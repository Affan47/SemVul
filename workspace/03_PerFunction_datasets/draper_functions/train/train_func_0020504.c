addtoken(const char str[], const unsigned int lineno, const unsigned int fileno, bool split)
{
    if (str[0] == 0)
        return;


    if (split && strstr(str, "##")) {
        std::string temp;
        for (unsigned int i = 0; str[i]; ++i) {
            if (strncmp(&str[i], "##", 2) == 0) {
                addtoken(temp.c_str(), lineno, fileno, false);
                temp.clear();
                addtoken("##", lineno, fileno, false);
                ++i;
            } else
                temp += str[i];
        }
        addtoken(temp.c_str(), lineno, fileno, false);
        return;
    }


    std::ostringstream str2;
    if (MathLib::isHex(str) || MathLib::isOct(str)) {
        str2 << MathLib::toLongNumber(str);
    } else if (strncmp(str, "_Bool", 5) == 0) {
        str2 << "bool";
    } else {
        str2 << str;
    }

    if (_back) {
        _back->insertToken(str2.str());
    } else {
        _front = new Token(&_back);
        _back = _front;
        _back->str(str2.str());
    }

    _back->linenr(lineno);
    _back->fileIndex(fileno);
}
