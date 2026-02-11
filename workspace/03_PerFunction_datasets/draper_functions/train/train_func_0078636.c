GetCase(const char* pszStr)
{
    int bInit = TRUE;
    char ch;
    CaseType eCase = CASE_UNKNOWN;
    while((ch = *(pszStr++)) != '\0')
    {
        if (bInit)
        {
            if (ch >= 'a' && ch <= 'z')
                eCase = CASE_LOWER;
            else if (ch >= 'A' && ch <= 'Z')
                eCase = CASE_UPPER;
            else
                return CASE_UNKNOWN;
        }
        else if (ch >= 'a' && ch <= 'z' && eCase == CASE_LOWER)
            ;
        else if (ch >= 'A' && ch <= 'Z' && eCase == CASE_UPPER)
            ;
        else
            return CASE_UNKNOWN;
    }
    return eCase;
}
