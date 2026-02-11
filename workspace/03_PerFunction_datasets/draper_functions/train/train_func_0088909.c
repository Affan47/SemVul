GetStyleString()
{
    if (m_pszStyleString == NULL)
    {


        char *pszSymbolStyleString = CPLStrdup(GetSymbolStyleString(GetSymbolAngle()));
        int nStyleStringlen = strlen(pszSymbolStyleString);
        pszSymbolStyleString[nStyleStringlen-1] = '\0';

        const char *outlineColor;
        if (m_nFontStyle & 16)
            outlineColor = ",o:#000000";
        else if (m_nFontStyle & 512)
            outlineColor = ",o:#ffffff";
        else
            outlineColor = "";

        m_pszStyleString = CPLStrdup(CPLSPrintf("%s%s)",
                                                pszSymbolStyleString,
                                                outlineColor));
        CPLFree(pszSymbolStyleString);
    }

    return m_pszStyleString;
}
