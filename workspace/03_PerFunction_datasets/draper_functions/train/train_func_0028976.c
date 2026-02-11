tr_strcpy( XMLCh *panXMLString, const char *pszCString )

{


    if( tr_isascii( pszCString ) )
    {
        while( *pszCString != 0 )
            *(panXMLString++) = *(pszCString++);
        *panXMLString = 0;
        return;
    }


    int i;
    wchar_t *pwszUTF16;

    pwszUTF16 = CPLRecodeToWChar( pszCString, CPL_ENC_UTF8, "WCHAR_T" );

    for( i = 0; pwszUTF16[i] != 0; i++ )
        panXMLString[i] = pwszUTF16[i];

    panXMLString[i] = 0;

    CPLFree( pwszUTF16 );
}
