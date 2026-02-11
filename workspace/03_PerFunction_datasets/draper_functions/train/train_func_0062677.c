VSICurlGetToken(char* pszCurPtr, char** ppszNextToken)
{
    if (pszCurPtr == NULL)
        return NULL;

    while((*pszCurPtr) == ' ')
        pszCurPtr ++;
    if (*pszCurPtr == '\0')
        return NULL;

    char* pszToken = pszCurPtr;
    while((*pszCurPtr) != ' ' && (*pszCurPtr) != '\0')
        pszCurPtr ++;
    if (*pszCurPtr == '\0')
        *ppszNextToken = NULL;
    else
    {
        *pszCurPtr = '\0';
        pszCurPtr ++;
        while((*pszCurPtr) == ' ')
            pszCurPtr ++;
        *ppszNextToken = pszCurPtr;
    }

    return pszToken;
}
