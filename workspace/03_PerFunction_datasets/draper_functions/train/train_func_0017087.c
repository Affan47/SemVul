DeleteFeature( long nFID )

{
    PGconn      *hPGConn = poDS->GetPGConn();
    PGresult    *hResult = NULL;
    CPLString   osCommand;

    GetLayerDefn();

    if( !bUpdateAccess )
    {
        CPLError( CE_Failure, CPLE_NotSupported,
                  UNSUPPORTED_OP_READ_ONLY,
                  "DeleteFeature");
        return OGRERR_FAILURE;
    }


    if( !bHasFid )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "DeleteFeature(%ld) failed.  Unable to delete features in tables without\n"
                  "a recognised FID column.",
                  nFID );
        return OGRERR_FAILURE;

    }


    osCommand.Printf( "DELETE FROM %s WHERE %s = %ld",
                      pszSqlTableName, OGRPGEscapeColumnName(pszFIDColumn).c_str(), nFID );


    OGRErr eErr;

    eErr = poDS->SoftStartTransaction();
    if( eErr != OGRERR_NONE )
        return eErr;

    hResult = OGRPG_PQexec(hPGConn, osCommand);

    if( PQresultStatus(hResult) != PGRES_COMMAND_OK )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "DeleteFeature() DELETE statement failed.\n%s",
                  PQerrorMessage(hPGConn) );

        OGRPGClearResult( hResult );

        poDS->SoftRollback();
        eErr = OGRERR_FAILURE;
    }
    else
    {
        OGRPGClearResult( hResult );

        eErr = poDS->SoftCommit();
    }

    return eErr;
}
