GDALDeregister_GTiff( GDALDriver * )

{
    CSVDeaccess( NULL );

#if defined(LIBGEOTIFF_VERSION) && LIBGEOTIFF_VERSION > 1150
    GTIFDeaccessCSV();
#endif

    if( hGTiffOneTimeInitMutex != NULL )
    {
        CPLDestroyMutex(hGTiffOneTimeInitMutex);
        hGTiffOneTimeInitMutex = NULL;
    }

    LibgeotiffOneTimeCleanupMutex();
}
