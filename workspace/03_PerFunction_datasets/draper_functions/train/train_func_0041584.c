fractionalPartToString(char* buf, int& i, const char* result, int resultLength, int fractionalDigits)
{
    if (fractionalDigits <= 0)
        return;

    int fDigitsInResult = static_cast<int>(resultLength) - 1;
    buf[i++] = '.';
    if (fDigitsInResult > 0) {
        if (fractionalDigits < fDigitsInResult) {
            strncpy(buf + i, result + 1, fractionalDigits);
            i += fractionalDigits;
        } else {
            strcpy(buf + i, result + 1);
            i += static_cast<int>(resultLength) - 1;
        }
    }

    for (int j = 0; j < fractionalDigits - fDigitsInResult; j++)
        buf[i++] = '0';
}
