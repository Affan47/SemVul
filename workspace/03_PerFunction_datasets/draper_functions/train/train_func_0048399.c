CPLRecodeToWCharStub( const char *pszSource,
                               const char *pszSrcEncoding,
                               const char *pszDstEncoding )

{
    char *pszUTF8Source = (char *) pszSource;

    if( strcmp(pszSrcEncoding,CPL_ENC_UTF8) != 0
        && strcmp(pszSrcEncoding,CPL_ENC_ASCII) != 0 )
    {
        pszUTF8Source = CPLRecodeStub( pszSource, pszSrcEncoding, CPL_ENC_UTF8 );
        if( pszUTF8Source == NULL )
            return NULL;
    }


    if( strcmp(pszDstEncoding,"WCHAR_T") != 0
        && strcmp(pszDstEncoding,CPL_ENC_UCS2) != 0
        && strcmp(pszDstEncoding,CPL_ENC_UCS4) != 0
        && strcmp(pszDstEncoding,CPL_ENC_UTF16) != 0 )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Stub recoding implementation does not support\n"
                  "CPLRecodeToWCharStub(...,%s,%s)",
                  pszSrcEncoding, pszDstEncoding );
        return NULL;
    }


    int nSrcLen = strlen(pszUTF8Source);
    wchar_t *pwszResult = (wchar_t *) CPLCalloc(sizeof(wchar_t),nSrcLen+1);

    utf8towc( pszUTF8Source, nSrcLen, pwszResult, nSrcLen+1 );

    if( pszUTF8Source != pszSource )
        CPLFree( pszUTF8Source );

    return pwszResult;
}
