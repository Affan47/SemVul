isInt(const std::string & s)
{


    if (s.find(".", 0) != std::string::npos) return false;

    else if (s.find("E-", 0) != std::string::npos || s.find("e-", 0) != std::string::npos) return false;


    enum Representation {
        eScientific = 0,
        eOctal,
        eHex,
        eDefault
    };

    Representation Mode = eDefault;


    unsigned long n = 0;

    while (std::isspace(s[n])) ++n;


    if (s.find("E", 0) != std::string::npos) {
        Mode = eScientific;
    } else if (isHex(s)) {
        Mode = eHex;
    } else if (isOct(s)) {
        Mode = eOctal;
    }


    if (s[n] == '-' || s[n] == '+') ++n;


    if (Mode == eScientific) {

        while (std::isdigit(s[n])) ++n;


        if (std::tolower(s[n]) == 'e') {
            ++n;

            if (s[n] == '+') ++n;

            if (s[n] == '-') return false;

            while (std::isdigit(s[n])) ++n;
        }
    }

    else if (Mode == eHex) {
        ++n;
        ++n;
        while (std::isxdigit(s[n]))
            ++n;

        while (std::tolower(s[n]) == 'u' || std::tolower(s[n]) == 'l') ++n;
    }

    else if (Mode == eOctal) {
        ++n;
        while (isOctalDigit(s[n]))
            ++n;

        while (std::tolower(s[n]) == 'u' || std::tolower(s[n]) == 'l') ++n;
    } else if (Mode == eDefault) {

        bool bStartsWithDigit=false;
        while (std::isdigit(s[n])) {
            bStartsWithDigit=true;
            ++n;
        };

        while (std::tolower(s[n]) == 'u' || std::tolower(s[n]) == 'l') ++n;

        if (!bStartsWithDigit)
            return false;
    }

    while (std::isspace(s[n]))
        ++n;


    return(n >= s.length());
}
