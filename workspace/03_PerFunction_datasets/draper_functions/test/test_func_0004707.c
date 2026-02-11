OGR_DS_Destroy( OGRDataSourceH hDS )

{
    VALIDATE_POINTER0( hDS, "OGR_DS_Destroy" );
    delete (OGRDataSource *) hDS;
}
