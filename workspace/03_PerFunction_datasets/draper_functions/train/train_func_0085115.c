Open( const char* pszName, int bUpdate,
                                       char** papszOptions )
{
    UNREFERENCED_PARAM(papszOptions);

    OGRGeoJSONDataSource* poDS = NULL;
    poDS = new OGRGeoJSONDataSource();


    poDS->SetGeometryTranslation( OGRGeoJSONDataSource::eGeometryPreserve );
    const char* pszOpt = CPLGetConfigOption("GEOMETRY_AS_COLLECTION", NULL);
    if( NULL != pszOpt && EQUALN(pszOpt, "YES", 3) )
    {
            poDS->SetGeometryTranslation(
                OGRGeoJSONDataSource::eGeometryAsCollection );
    }

    poDS->SetAttributesTranslation( OGRGeoJSONDataSource::eAtributesPreserve );
    pszOpt = CPLGetConfigOption("ATTRIBUTES_SKIP", NULL);
    if( NULL != pszOpt && EQUALN(pszOpt, "YES", 3) )
    {
        poDS->SetAttributesTranslation(
            OGRGeoJSONDataSource::eAtributesSkip );
    }


    if( !poDS->Open( pszName ) )
    {
        delete poDS;
        poDS= NULL;
    }

    if( NULL != poDS && bUpdate )
    {
        CPLError( CE_Failure, CPLE_OpenFailed,
                  "GeoJSON Driver doesn't support update." );
        delete poDS;
        return NULL;
    }

    return poDS;
}
