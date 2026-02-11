DBFClose(DBFHandle psDBF)
{
    static char eof = 0x1a;
    char eof_test;


    if( psDBF->bNoHeader )
        DBFWriteHeader( psDBF );

    DBFFlushRecord( psDBF );


    if( psDBF->bUpdated )
        DBFUpdateHeader( psDBF );


    fseek(psDBF->fp, -1, SEEK_END);
    fread(&eof_test, 1, 1, psDBF->fp);
    if( eof_test != 0x1a )
    {
        fseek(psDBF->fp, 0, SEEK_END);
        fwrite(&eof, 1, 1, psDBF->fp);
    }


    fclose( psDBF->fp );

    if( psDBF->panFieldOffset != NULL )
    {
        free( psDBF->panFieldOffset );
        free( psDBF->panFieldSize );
        free( psDBF->panFieldDecimals );
        free( psDBF->pachFieldType );
    }

    free( psDBF->pszHeader );
    free( psDBF->pszCurrentRecord );

    free( psDBF );

    if( pszStringField != NULL )
    {
        free( pszStringField );
        pszStringField = NULL;
        nStringFieldLen = 0;
    }
}
