addtoken(const std::string & str, const unsigned int lineno, const unsigned int fileno, bool split)
{
    if (str.empty())
        return;


    if (split) {
        size_t begin = 0;
        size_t end = 0;
        while ((end = str.find("##", begin)) != std::string::npos) {
            addtoken(str.substr(begin, end - begin), lineno, fileno, false);
            addtoken("##", lineno, fileno, false);
            begin = end+2;
        }
        if (begin != 0) {
            addtoken(str.substr(begin), lineno, fileno, false);
            return;
        }
    }


    std::string str2;
    if (MathLib::isHex(str) || MathLib::isOct(str) || MathLib::isBin(str)) {
        std::ostringstream str2stream;
        str2stream << MathLib::toLongNumber(str);
        str2 = str2stream.str();
    } else if (str.compare(0, 5, "_Bool") == 0) {
        str2 = "bool";
    } else {
        str2 = str;
    }

    if (_back) {
        _back->insertToken(str2);
    } else {
        _front = new Token(&_back);
        _back = _front;
        _back->str(str2);
    }

    if (isCPP() && str == "delete")
        _back->isKeyword(true);
    _back->linenr(lineno);
    _back->fileIndex(fileno);
}
