identifyBase(char c)
{
    if (c == '\'')
        return 8;
    else if (c == '"')
        return 16;
    else if (c == '`')
        return -1;
    else if (isdigit(c))
        return 10;
    else
        return 0;
}
