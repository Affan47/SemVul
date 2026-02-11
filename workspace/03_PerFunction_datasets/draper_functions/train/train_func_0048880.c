CloseCursor()
{
    PGconn      *hPGConn = poDS->GetPGConn();

    if( hCursorResult != NULL )
    {
        OGRPGClearResult( hCursorResult );

        CPLString    osCommand;
        osCommand.Printf("CLOSE %s", pszCursorName );

        hCursorResult = OGRPG_PQexec(hPGConn, osCommand.c_str());
        OGRPGClearResult( hCursorResult );

        poDS->FlushSoftTransaction();

        hCursorResult = NULL;
    }
}
