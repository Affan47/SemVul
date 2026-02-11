Initialize( const char *pszTableName,
                                        const char *pszGeomCol,
                                        int bMustIncludeGeomColName,
                                        OGRwkbGeometryType eGeomType,
                                        const char *pszGeomFormat,
                                        OGRSpatialReference *poSRS,
                                        int nSRSId,
                                        int bHasSpatialIndex,
                                        int bHasM,
                                        int bIsVirtualShapeIn )

{
    int rc;
    sqlite3 *hDB = poDS->GetDB();

    if( pszGeomCol == NULL )
        osGeomColumn = "";
    else
        osGeomColumn = pszGeomCol;

    if( pszGeomFormat )
    {
        if ( EQUAL(pszGeomFormat, "WKT") )
            eGeomFormat = OSGF_WKT;
        else if ( EQUAL(pszGeomFormat,"WKB") )
            eGeomFormat = OSGF_WKB;
        else if ( EQUAL(pszGeomFormat,"FGF") )
            eGeomFormat = OSGF_FGF;
        else if( EQUAL(pszGeomFormat,"SpatiaLite") )
            eGeomFormat = OSGF_SpatiaLite;
    }

    CPLFree( pszFIDColumn );
    pszFIDColumn = NULL;

    if( nSRSId == UNINITIALIZED_SRID )
        nSRSId = poDS->GetUndefinedSRID();

    this->poSRS = poSRS;
    this->nSRSId = nSRSId;
    this->bHasSpatialIndex = bHasSpatialIndex;
    this->bHasM = bHasM;
    this->bIsVirtualShape = bIsVirtualShapeIn;
    this->pszTableName = CPLStrdup(pszTableName);
    this->eGeomType = eGeomType;

    if( bMustIncludeGeomColName )
        osLayerName.Printf("%s(%s)", pszTableName, osGeomColumn.c_str());
    else
        osLayerName = pszTableName;

    pszEscapedTableName = CPLStrdup(OGRSQLiteEscape(pszTableName));

    sqlite3_stmt *hColStmt = NULL;
    const char *pszSQL;

    if ( eGeomFormat == OSGF_SpatiaLite &&
         OGRSQLiteIsSpatialiteLoaded() &&
         OGRSQLiteGetSpatialiteVersionNumber() < 24 && poDS->GetUpdate() )
    {

        hColStmt = NULL;
        pszSQL = CPLSPrintf( "SELECT sql FROM sqlite_master WHERE type = 'trigger' AND tbl_name = '%s' AND sql LIKE '%%RTreeAlign%%'",
            pszEscapedTableName );

        int nRowTriggerCount, nColTriggerCount;
        char **papszTriggerResult, *pszErrMsg;

        rc = sqlite3_get_table( hDB, pszSQL, &papszTriggerResult,
            &nRowTriggerCount, &nColTriggerCount, &pszErrMsg );
        if( nRowTriggerCount >= 1 )
        {


            CPLDebug("SQLITE", "Enforcing ReadOnly mode : obsolete library version not supporting new triggers");
            poDS->SetUpdate(FALSE);
        }

        sqlite3_free_table( papszTriggerResult );
    }

    if( poSRS )
        poSRS->Reference();

    LoadStatistics();

    return CE_None;
}
