GDALGetDriverLongName( GDALDriverH hDriver )

{
    VALIDATE_POINTER1( hDriver, "GDALGetDriverLongName", NULL );

    const char *pszLongName =
        ((GDALDriver *) hDriver)->GetMetadataItem( GDAL_DMD_LONGNAME );

    if( pszLongName == NULL )
        return "";
    else
        return pszLongName;
}
