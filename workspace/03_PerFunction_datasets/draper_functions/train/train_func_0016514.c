OGR2SQLITEExtractUnquotedString(const char **ppszSQLCommand)
{
    CPLString osRet;
    const char *pszSQLCommand = *ppszSQLCommand;
    char chQuoteChar = 0;

    if( *pszSQLCommand == '"' || *pszSQLCommand == '\'' )
    {
        chQuoteChar = *pszSQLCommand;
        pszSQLCommand ++;
    }

    while( *pszSQLCommand != '\0' )
    {
        if( *pszSQLCommand == chQuoteChar &&
            pszSQLCommand[1] == chQuoteChar )
        {
            pszSQLCommand ++;
            osRet += chQuoteChar;
        }
        else if( *pszSQLCommand == chQuoteChar )
        {
            pszSQLCommand ++;
            break;
        }
        else if( chQuoteChar == '\0' &&
                (isspace((int)*pszSQLCommand) ||
                 *pszSQLCommand == '.' ||
                 *pszSQLCommand == ')' ||
                 *pszSQLCommand == ',') )
            break;
        else
            osRet += *pszSQLCommand;

        pszSQLCommand ++;
    }

    *ppszSQLCommand = pszSQLCommand;

    return osRet;
}
