CPLForceToASCII(const char* pabyData, int nLen, char chReplacementChar)
{
    if (nLen < 0)
        nLen = strlen(pabyData);
    char* pszOutputString = (char*)CPLMalloc(nLen + 1);
    int i;
    for(i=0;i<nLen;i++)
    {
        if (((unsigned char*)pabyData)[i] > 127)
            pszOutputString[i] = chReplacementChar;
        else
            pszOutputString[i] = pabyData[i];
    }
    pszOutputString[i] = '\0';
    return pszOutputString;
}
