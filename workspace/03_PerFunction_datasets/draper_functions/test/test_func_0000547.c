DBFCreate( const char * pszFilename )

{
    DBFHandle	psDBF;
    FILE	*fp;
    char	*pszFullname, *pszBasename;
    int		i;


    pszBasename = (char *) malloc(strlen(pszFilename)+5);
    strcpy( pszBasename, pszFilename );
    for( i = strlen(pszBasename)-1;
	 i > 0 && pszBasename[i] != '.' && pszBasename[i] != '/'
	       && pszBasename[i] != '\\';
	 i-- ) {}

    if( pszBasename[i] == '.' )
        pszBasename[i] = '\0';

    pszFullname = (char *) malloc(strlen(pszBasename) + 5);
    sprintf( pszFullname, "%s.dbf", pszBasename );
    free( pszBasename );


    fp = fopen( pszFullname, "wb" );
    if( fp == NULL )
        return( NULL );

    fputc( 0, fp );
    fclose( fp );

    fp = fopen( pszFullname, "rb+" );
    if( fp == NULL )
        return( NULL );

    free( pszFullname );


    psDBF = (DBFHandle) malloc(sizeof(DBFInfo));

    psDBF->fp = fp;
    psDBF->nRecords = 0;
    psDBF->nFields = 0;
    psDBF->nRecordLength = 1;
    psDBF->nHeaderLength = 33;
    psDBF->bUpdated = FALSE;

    psDBF->panFieldOffset = NULL;
    psDBF->panFieldSize = NULL;
    psDBF->panFieldDecimals = NULL;
    psDBF->pachFieldType = NULL;
    psDBF->pszHeader = NULL;

    psDBF->nCurrentRecord = -1;
    psDBF->bCurrentRecordModified = FALSE;
    psDBF->pszCurrentRecord = NULL;

    psDBF->bNoHeader = TRUE;

    return( psDBF );
}
