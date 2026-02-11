OGR_Dr_Open( OGRSFDriverH hDriver, const char *pszName,
                            int bUpdate )

{
    VALIDATE_POINTER1( hDriver, "OGR_Dr_Open", NULL );

    OGRDataSource *poDS = ((OGRSFDriver *)hDriver)->Open( pszName, bUpdate );

    if( poDS != NULL && poDS->GetDriver() == NULL )
        poDS->SetDriver( (OGRSFDriver *)hDriver );

    return (OGRDataSourceH) poDS;
}
