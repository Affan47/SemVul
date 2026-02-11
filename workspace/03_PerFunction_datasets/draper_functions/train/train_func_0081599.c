SetFeature( OGRFeature *poFeature )

{
    if (HasLayerDefnError())
        return OGRERR_FAILURE;

    if( pszFIDColumn == NULL )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "SetFeature() without any FID column." );
        return OGRERR_FAILURE;
    }

    if( poFeature->GetFID() == OGRNullFID )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "SetFeature() with unset FID fails." );
        return OGRERR_FAILURE;
    }

    if (!poDS->GetUpdate())
    {
        CPLError( CE_Failure, CPLE_NotSupported,
                  UNSUPPORTED_OP_READ_ONLY,
                  "SetFeature");
        return OGRERR_FAILURE;
    }

    sqlite3 *hDB = poDS->GetDB();
    CPLString      osCommand;
    int            bNeedComma = FALSE;

    ResetReading();


    osCommand += CPLSPrintf( "UPDATE '%s' SET ", pszEscapedTableName );


    if( osGeomColumn.size() != 0 &&
        eGeomFormat != OSGF_FGF )
    {
        osCommand += "\"";
        osCommand += OGRSQLiteEscapeName(osGeomColumn);
        osCommand += "\" = ?";

        bNeedComma = TRUE;
    }


    int iField;
    int nFieldCount = poFeatureDefn->GetFieldCount();

    for( iField = 0; iField < nFieldCount; iField++ )
    {
        if( bNeedComma )
            osCommand += ",";

        osCommand += "\"";
        osCommand += OGRSQLiteEscapeName(poFeatureDefn->GetFieldDefn(iField)->GetNameRef());
        osCommand += "\" = ?";

        bNeedComma = TRUE;
    }

    if (!bNeedComma)
        return OGRERR_NONE;


    osCommand += " WHERE \"";
    osCommand += OGRSQLiteEscapeName(pszFIDColumn);
    osCommand += CPLSPrintf("\" = %ld", poFeature->GetFID());


    int rc;
    sqlite3_stmt *hUpdateStmt;

#ifdef DEBUG
    CPLDebug( "OGR_SQLITE", "prepare(%s)", osCommand.c_str() );
#endif

    rc = sqlite3_prepare( hDB, osCommand, -1, &hUpdateStmt, NULL );
    if( rc != SQLITE_OK )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "In SetFeature(): sqlite3_prepare(%s):\n  %s",
                  osCommand.c_str(), sqlite3_errmsg(hDB) );

        return OGRERR_FAILURE;
    }


    OGRErr eErr = BindValues( poFeature, hUpdateStmt, TRUE );
    if (eErr != OGRERR_NONE)
    {
        sqlite3_finalize( hUpdateStmt );
        return eErr;
    }


    rc = sqlite3_step( hUpdateStmt );

    if( rc != SQLITE_OK && rc != SQLITE_DONE )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "sqlite3_step() failed:\n  %s",
                  sqlite3_errmsg(hDB) );

        sqlite3_finalize( hUpdateStmt );
        return OGRERR_FAILURE;
    }

    sqlite3_finalize( hUpdateStmt );

    OGRGeometry *poGeom = poFeature->GetGeometryRef();
    if( bCachedExtentIsValid &&
        poGeom != NULL && !poGeom->IsEmpty() )
    {
        OGREnvelope sGeomEnvelope;
        poGeom->getEnvelope(&sGeomEnvelope);
        oCachedExtent.Merge(sGeomEnvelope);
    }
    bStatisticsNeedsToBeFlushed = TRUE;

    return OGRERR_NONE;
}
