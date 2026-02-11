PAuxDelete( const char * pszBasename )

{
    VSILFILE	*fp;
    const char *pszLine;

    fp = VSIFOpenL( CPLResetExtension( pszBasename, "aux" ), "r" );
    if( fp == NULL )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "%s does not appear to be a PAux dataset, there is no .aux file.",
                  pszBasename );
        return CE_Failure;
    }

    pszLine = CPLReadLineL( fp );
    VSIFCloseL( fp );

    if( pszLine == NULL || !EQUALN(pszLine,"AuxilaryTarget",14) )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "%s does not appear to be a PAux dataset,\n"
                  "the .aux file does not start with AuxilaryTarget",
                  pszBasename );
        return CE_Failure;
    }

    if( VSIUnlink( pszBasename ) != 0 )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "OS unlinking file %s.", pszBasename );
        return CE_Failure;
    }

    VSIUnlink( CPLResetExtension( pszBasename, "aux" ) );

    return CE_None;
}
