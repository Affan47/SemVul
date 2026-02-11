addtoken(const char str[], const unsigned int lineno, const unsigned int fileno, bool split)
{
    if (str[0] == 0)
        return;


    if (split && strstr(str, "##"))
    {
        std::string temp;
        for (unsigned int i = 0; str[i]; ++i)
        {
            if (strncmp(&str[i], "##", 2) == 0)
            {
                addtoken(temp.c_str(), lineno, fileno, false);
                temp.clear();
                addtoken("##", lineno, fileno, false);
                ++i;
            }
            else
                temp += str[i];
        }
        addtoken(temp.c_str(), lineno, fileno, false);
        return;
    }


    std::ostringstream str2;
    if (strncmp(str, "0x", 2) == 0 || strncmp(str, "0X", 2) == 0)
    {
        str2 << std::strtoul(str + 2, NULL, 16);
    }
    else
    {
        str2 << str;
    }

    if (_tokensBack)
    {
        _tokensBack->insertToken(str2.str().c_str());
    }
    else
    {
        _tokens = new Token(&_tokensBack);
        _tokensBack = _tokens;
        _tokensBack->str(str2.str());
    }

    _tokensBack->linenr(lineno);
    _tokensBack->fileIndex(fileno);
}
