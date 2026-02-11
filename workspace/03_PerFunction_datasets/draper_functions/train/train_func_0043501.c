GetSpatialRef()

{
    if( nSRSId == UNDETERMINED_SRID )
    {
        PGconn      *hPGConn = poDS->GetPGConn();
        PGresult    *hResult = NULL;
        CPLString    osCommand;

        nSRSId = poDS->GetUndefinedSRID();

        poDS->SoftStartTransaction();

        osCommand.Printf(
                    "SELECT srid FROM geometry_columns "
                    "WHERE f_table_name = '%s'",
                    pszTableName);

        if (pszGeomColumn)
        {
            osCommand += CPLString().Printf(" AND f_geometry_column = '%s'", pszGeomColumn);
        }

        if (pszSchemaName)
        {
            osCommand += CPLString().Printf(" AND f_table_schema = '%s'", pszSchemaName);
        }

        hResult = OGRPG_PQexec(hPGConn, osCommand.c_str() );

        if( hResult
            && PQresultStatus(hResult) == PGRES_TUPLES_OK
            && PQntuples(hResult) == 1 )
        {
            nSRSId = atoi(PQgetvalue(hResult,0,0));
        }

        OGRPGClearResult( hResult );

        poDS->SoftCommit();
    }

    return OGRPGLayer::GetSpatialRef();
}
