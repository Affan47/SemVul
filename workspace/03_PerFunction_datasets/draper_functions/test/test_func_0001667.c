FindAlphaNum(char *srcStr, unsigned int *sLen)
{
    char curChar;
    char *foundStr;

    while (*srcStr != '\0')
    {
        curChar = toupper(*srcStr);
        if ((curChar >= 'A') && (curChar <= 'Z'))
            break;

        if ((curChar >= '0') && (curChar <='9'))
            break;

        if (curChar == '_')
            break;

        srcStr++;
    }

    if (*srcStr == '\0')
    {
        return NULL;
    }

    foundStr = srcStr;

    *sLen = 0;

    while (*srcStr != '\0')
    {
        curChar = toupper(*srcStr);
        if ((curChar < 'A') || (curChar > 'Z'))
        {
            if ((curChar < '0') || (curChar > '9'))
            {
                if (curChar != '_')
                    break;
            }
        }

        (*sLen)++;
        srcStr++;
    }

    return foundStr;

}
