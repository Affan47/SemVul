toULongNumber(const std::string & str)
{

    if (isHex(str)) {
        if (str[0] == '-') {
            biguint ret = 0;
            std::istringstream istr(str);
            istr >> std::hex >> ret;
            return ret;
        } else {
            unsigned long long ret = 0;
            std::istringstream istr(str);
            istr >> std::hex >> ret;
            return (biguint)ret;
        }
    }


    if (isOct(str)) {
        biguint ret = 0;
        std::istringstream istr(str);
        istr >> std::oct >> ret;
        return ret;
    }


    if (isBin(str)) {
        biguint ret = 0;
        for (std::string::size_type i = str[0] == '0'?2:3; i < str.length(); i++) {
            ret <<= 1;
            if (str[i] == '1')
                ret |= 1;
        }


        return ret;
    }

    if (isFloat(str)) {


        const double doubleval = std::atof(str.c_str());
        if (doubleval > (double)std::numeric_limits<biguint>::max())
            return std::numeric_limits<biguint>::max();
        else
            return static_cast<biguint>(doubleval);
    }

    biguint ret = 0;
    std::istringstream istr(str);
    istr >> ret;
    return ret;
}
