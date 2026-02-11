OGRGPX_GetUTF8String(const char* pszString)
{
    char *pszEscaped;
    if (!CPLIsUTF8(pszString, -1) &&
         CSLTestBoolean(CPLGetConfigOption("OGR_FORCE_ASCII", "YES")))
    {
        static int bFirstTime = TRUE;
        if (bFirstTime)
        {
            bFirstTime = FALSE;
            CPLError(CE_Warning, CPLE_AppDefined,
                    "%s is not a valid UTF-8 string. Forcing it to ASCII.\n"
                    "If you still want the original string and change the XML file encoding\n"
                    "afterwards, you can define OGR_FORCE_ASCII=NO as configuration option.\n"
                    "This warning won't be issued anymore", pszString);
        }
        else
        {
            CPLDebug("OGR", "%s is not a valid UTF-8 string. Forcing it to ASCII",
                    pszString);
        }
        pszEscaped = CPLForceToASCII(pszString, -1, '?');
    }
    else
        pszEscaped = CPLStrdup(pszString);

    return pszEscaped;
}
