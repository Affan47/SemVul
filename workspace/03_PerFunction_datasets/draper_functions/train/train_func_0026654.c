SetWellKnownGeogCS( const char * pszName )

{
    OGRSpatialReference   oSRS2;
    OGRErr eErr;


    if( EQUALN(pszName, "EPSG:",5) )
    {
        eErr = oSRS2.importFromEPSG( atoi(pszName+5) );
        if( eErr != OGRERR_NONE )
            return eErr;

        if( !oSRS2.IsGeographic() )
            return OGRERR_FAILURE;

        return CopyGeogCSFrom( &oSRS2 );
    }


    if( EQUALN(pszName, "EPSGA:",6) )
    {
        eErr = oSRS2.importFromEPSGA( atoi(pszName+6) );
        if( eErr != OGRERR_NONE )
            return eErr;

        if( !oSRS2.IsGeographic() )
            return OGRERR_FAILURE;

        return CopyGeogCSFrom( &oSRS2 );
    }


    char        *pszWKT = NULL;

    if( EQUAL(pszName, "WGS84") || EQUAL(pszName,"CRS84") || EQUAL(pszName,"CRS:84") )
        pszWKT = (char* ) SRS_WKT_WGS84;

    else if( EQUAL(pszName, "WGS72") )
        pszWKT = (char* ) "GEOGCS[\"WGS 72\",DATUM[\"WGS_1972\",SPHEROID[\"WGS 72\",6378135,298.26,AUTHORITY[\"EPSG\",\"7043\"]],TOWGS84[0,0,4.5,0,0,0.554,0.2263],AUTHORITY[\"EPSG\",\"6322\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.0174532925199433,AUTHORITY[\"EPSG\",\"9108\"]],AUTHORITY[\"EPSG\",\"4322\"]]";

    else if( EQUAL(pszName, "NAD27") || EQUAL(pszName, "CRS27") || EQUAL(pszName,"CRS:27") )
        pszWKT = (char* ) "GEOGCS[\"NAD27\",DATUM[\"North_American_Datum_1927\",SPHEROID[\"Clarke 1866\",6378206.4,294.978698213898,AUTHORITY[\"EPSG\",\"7008\"]],AUTHORITY[\"EPSG\",\"6267\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.0174532925199433,AUTHORITY[\"EPSG\",\"9108\"]],AUTHORITY[\"EPSG\",\"4267\"]]";

    else if( EQUAL(pszName, "NAD83") || EQUAL(pszName,"CRS83") || EQUAL(pszName,"CRS:83") )
        pszWKT = (char* ) "GEOGCS[\"NAD83\",DATUM[\"North_American_Datum_1983\",SPHEROID[\"GRS 1980\",6378137,298.257222101,AUTHORITY[\"EPSG\",\"7019\"]],TOWGS84[0,0,0,0,0,0,0],AUTHORITY[\"EPSG\",\"6269\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.0174532925199433,AUTHORITY[\"EPSG\",\"9108\"]],AUTHORITY[\"EPSG\",\"4269\"]]";

    else
        return OGRERR_FAILURE;


    eErr = oSRS2.importFromWkt( &pszWKT );
    if( eErr != OGRERR_NONE )
        return eErr;


    return CopyGeogCSFrom( &oSRS2 );
}
