isOct(const std::string& s)
{
    enum Status {
        START, PLUSMINUS, OCTAL_PREFIX, DIGITS
    } state = START;
    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
        switch (state) {
        case START:
            if (*it == '+' || *it == '-')
                state = PLUSMINUS;
            else if (*it == '0')
                state = OCTAL_PREFIX;
            else
                return false;
            break;
        case PLUSMINUS:
            if (*it == '0')
                state = OCTAL_PREFIX;
            else
                return false;
            break;
        case OCTAL_PREFIX:
            if (isOctalDigit(*it))
                state = DIGITS;
            else
                return false;
            break;
        case DIGITS:
            if (isOctalDigit(*it))
                state = DIGITS;
            else
                return isValidSuffix(it,s.end());
            break;
        }
    }
    return state == DIGITS;
}
