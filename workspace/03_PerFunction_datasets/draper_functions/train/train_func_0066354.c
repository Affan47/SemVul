CSVDetectSeperator (const char* pszLine)
{
    int     bInString = FALSE;
    char    chDelimiter = '\0';

    for( ; *pszLine != '\0'; pszLine++ )
    {
        if( !bInString && (*pszLine == ',' || *pszLine == ';' || *pszLine == '\t'))
        {
            if (chDelimiter == '\0')
                chDelimiter = *pszLine;
            else if (chDelimiter != *pszLine)
            {

                CPLDebug("CSV", "Inconsistent separator. '%c' and '%c' found. Using ',' as default",
                         chDelimiter, *pszLine);
                chDelimiter = ',';
                break;
            }
        }
        else if( *pszLine == '"' )
        {
            if( !bInString || pszLine[1] != '"' )
            {
                bInString = !bInString;
                continue;
            }
            else
            {
                pszLine++;
            }
        }
    }

    if (chDelimiter == '\0')
        chDelimiter = ',';

    return chDelimiter;
}
