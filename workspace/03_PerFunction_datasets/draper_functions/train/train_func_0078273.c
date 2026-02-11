OGRPGTokenizeStringListFromText(const char* pszText)
{
    char** papszTokens = NULL;
    const char* pszCur = strchr(pszText, '{');
    if (pszCur == NULL)
    {
        CPLError(CE_Warning, CPLE_AppDefined, "Incorrect string list : %s", pszText);
        return papszTokens;
    }

    const char* pszNewTokenStart = NULL;
    int bInDoubleQuotes = FALSE;
    pszCur ++;
    while(*pszCur)
    {
        if (*pszCur == '\\')
        {
            pszCur ++;
            if (*pszCur == 0)
                break;
            pszCur ++;
            continue;
        }

        if (*pszCur == '"')
        {
            bInDoubleQuotes = !bInDoubleQuotes;
            if (bInDoubleQuotes)
                pszNewTokenStart = pszCur + 1;
            else
            {
                if (pszCur[1] == ',' || pszCur[1] == '}')
                {
                    if (pszNewTokenStart != NULL && pszCur > pszNewTokenStart)
                    {
                        char* pszNewToken = (char*) CPLMalloc(pszCur - pszNewTokenStart + 1);
                        memcpy(pszNewToken, pszNewTokenStart, pszCur - pszNewTokenStart);
                        pszNewToken[pszCur - pszNewTokenStart] = 0;
                        OGRPGTokenizeStringListUnescapeToken(pszNewToken);
                        papszTokens = CSLAddString(papszTokens, pszNewToken);
                        CPLFree(pszNewToken);
                    }
                    pszNewTokenStart = NULL;
                    if (pszCur[1] == ',')
                        pszCur ++;
                    else
                        return papszTokens;
                }
                else
                {

                    break;
                }
            }
        }
        if (!bInDoubleQuotes)
        {
            if (*pszCur == '{')
            {

                break;
            }
            else if (*pszCur == '}')
            {
                if (pszNewTokenStart != NULL && pszCur > pszNewTokenStart)
                {
                    char* pszNewToken = (char*) CPLMalloc(pszCur - pszNewTokenStart + 1);
                    memcpy(pszNewToken, pszNewTokenStart, pszCur - pszNewTokenStart);
                    pszNewToken[pszCur - pszNewTokenStart] = 0;
                    OGRPGTokenizeStringListUnescapeToken(pszNewToken);
                    papszTokens = CSLAddString(papszTokens, pszNewToken);
                    CPLFree(pszNewToken);
                }
                return papszTokens;
            }
            else if (*pszCur == ',')
            {
                if (pszNewTokenStart != NULL && pszCur > pszNewTokenStart)
                {
                    char* pszNewToken = (char*) CPLMalloc(pszCur - pszNewTokenStart + 1);
                    memcpy(pszNewToken, pszNewTokenStart, pszCur - pszNewTokenStart);
                    pszNewToken[pszCur - pszNewTokenStart] = 0;
                    OGRPGTokenizeStringListUnescapeToken(pszNewToken);
                    papszTokens = CSLAddString(papszTokens, pszNewToken);
                    CPLFree(pszNewToken);
                }
                pszNewTokenStart = pszCur + 1;
            }
            else if (pszNewTokenStart == NULL)
                pszNewTokenStart = pszCur;
        }
        pszCur++;
    }

    CPLError(CE_Warning, CPLE_AppDefined, "Incorrect string list : %s", pszText);
    return papszTokens;
}
