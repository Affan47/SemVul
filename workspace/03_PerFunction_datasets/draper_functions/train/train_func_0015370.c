GetSpatialWhere(OGRGeometry* poFilterGeom)
{
    CPLString osSpatialWHERE;

    if( !poDS->IsSpatialiteDB() )
        return osSpatialWHERE;

    if( poFilterGeom != NULL && CheckSpatialIndexTable() )
    {
        OGREnvelope  sEnvelope;

        CPLLocaleC  oLocaleEnforcer;

        poFilterGeom->getEnvelope( &sEnvelope );

        osSpatialWHERE.Printf("ROWID IN ( SELECT pkid FROM 'idx_%s_%s' WHERE "
                        "xmax >= %.12f AND xmin <= %.12f AND ymax >= %.12f AND ymin <= %.12f)",
                        pszEscapedTableName, OGRSQLiteEscape(osGeomColumn).c_str(),
                        sEnvelope.MinX - 1e-11, sEnvelope.MaxX + 1e-11,
                        sEnvelope.MinY - 1e-11, sEnvelope.MaxY + 1e-11);
    }

    if( poFilterGeom != NULL &&
        OGRSQLiteIsSpatialiteLoaded() && !bHasSpatialIndex )
    {
        OGREnvelope  sEnvelope;

        CPLLocaleC  oLocaleEnforcer;

        poFilterGeom->getEnvelope( &sEnvelope );


        osSpatialWHERE.Printf("MBRIntersects(\"%s\", BuildMBR(%.12f, %.12f, %.12f, %.12f, %d))",
                       OGRSQLiteEscapeName(osGeomColumn).c_str(),
                       sEnvelope.MinX - 1e-11, sEnvelope.MinY - 1e-11,
                       sEnvelope.MaxX + 1e-11, sEnvelope.MaxY + 1e-11,
                       nSRSId);
    }

    return osSpatialWHERE;
}
