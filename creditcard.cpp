#include <iostream>
#include <string>
#include <algorithm>

int sumDigits(int number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

bool isValidCreditCard(const std::string& cardNumber) {
    // Remove whitespace and non-digit characters
    std::string number = cardNumber;
    number.erase(std::remove_if(number.begin(), number.end(), [](char c) { return !std::isdigit(c); }), number.end());

    int numDigits = number.length();
    int sum = 0;
    bool isSecondDigit = false;

    for (int i = numDigits - 1; i >= 0; i--) {
        int digit = number[i] - '0';

        if (isSecondDigit) {
            digit *= 2;
            digit = sumDigits(digit);
        }

        sum += digit;
        isSecondDigit = !isSecondDigit;
    }

    if (sum % 10 != 0) {
        return false;
    }

    // Check card type based on number patterns
    if (number[0] == '4' && (numDigits == 13 || numDigits == 16)) {
        std::cout << "Card type: Visa\n";
    } else if (number.substr(0, 2) == "51" || number.substr(0, 2) == "52" || number.substr(0, 2) == "53" || number.substr(0, 2) == "54" || number.substr(0, 2) == "55") {
        if (numDigits == 16) {
            std::cout << "Card type: Mastercard\n";
        } else {
            std::cout << "Invalid card type\n";
            return false;
        }
    } else if ((number.substr(0, 2) == "34" || number.substr(0, 2) == "37") && numDigits == 15) {
        std::cout << "Card type: American Express\n";
    } else if (number.substr(0, 4) == "6011" && numDigits == 16) {
        std::cout << "Card type: Discover\n";
    } else {
        std::cout << "Invalid card type\n";
        return false;
    }

    return true;
}

int main() {
    std::string cardNumber;
    std::cout << "Enter credit card number: ";
    std::getline(std::cin, cardNumber);

    if (isValidCreditCard(cardNumber)) {
        std::cout << "Valid credit card number.\n";
    } else {
        std::cout << "Invalid credit card number.\n";
    }

    return 0;
}
