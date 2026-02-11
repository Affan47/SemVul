DeleteField( int iField )
{
    PGconn              *hPGConn = poDS->GetPGConn();
    PGresult            *hResult = NULL;
    CPLString           osCommand;

    GetLayerDefn();

    if( !bUpdateAccess )
    {
        CPLError( CE_Failure, CPLE_NotSupported,
                  UNSUPPORTED_OP_READ_ONLY,
                  "DeleteField");
        return OGRERR_FAILURE;
    }

    if (iField < 0 || iField >= poFeatureDefn->GetFieldCount())
    {
        CPLError( CE_Failure, CPLE_NotSupported,
                  "Invalid field index");
        return OGRERR_FAILURE;
    }

    poDS->FlushSoftTransaction();

    hResult = OGRPG_PQexec(hPGConn, "BEGIN");
    OGRPGClearResult( hResult );

    osCommand.Printf( "ALTER TABLE %s DROP COLUMN %s",
                      pszSqlTableName,
                      OGRPGEscapeColumnName(poFeatureDefn->GetFieldDefn(iField)->GetNameRef()).c_str() );
    hResult = OGRPG_PQexec(hPGConn, osCommand);
    if( PQresultStatus(hResult) != PGRES_COMMAND_OK )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "%s\n%s",
                  osCommand.c_str(),
                  PQerrorMessage(hPGConn) );

        OGRPGClearResult( hResult );

        hResult = OGRPG_PQexec( hPGConn, "ROLLBACK" );
        OGRPGClearResult( hResult );

        return OGRERR_FAILURE;
    }

    OGRPGClearResult( hResult );

    hResult = OGRPG_PQexec(hPGConn, "COMMIT");
    OGRPGClearResult( hResult );

    return poFeatureDefn->DeleteFieldDefn( iField );
}
