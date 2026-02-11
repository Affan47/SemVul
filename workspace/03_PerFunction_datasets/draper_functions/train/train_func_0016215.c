UnstackTokens(const char* pszToken,
                                    int nRequiredArgs,
                                    char aszTokenStack[TOKEN_STACK_SIZE][MAX_TOKEN_SIZE],
                                    int& nTokenStackSize,
                                    double* adfCoords)
{
    if (nTokenStackSize < nRequiredArgs)
    {
        CPLDebug("PDF", "not enough arguments for %s", pszToken);
        return FALSE;
    }
    nTokenStackSize -= nRequiredArgs;
    for(int i=0;i<nRequiredArgs;i++)
    {
        adfCoords[i] = atof(aszTokenStack[nTokenStackSize+i]);
    }
    return TRUE;
}
