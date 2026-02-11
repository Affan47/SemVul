OpenFile( const char *pszFilename ) {
    fpItf = VSIFOpen( pszFilename, "r" );
    if( fpItf == NULL )
    {
          CPLError( CE_Failure, CPLE_OpenFailed,
                    "Failed to open ILI file `%s'.",
                    pszFilename );

        return FALSE;
    }
    return TRUE;
}
