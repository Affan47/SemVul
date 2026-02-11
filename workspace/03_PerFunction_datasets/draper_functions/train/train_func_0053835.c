OGRCleanupAll()

{
    {


        CPLMutexHolderD( &hDRMutex );

        if( poRegistrar != NULL )
            delete poRegistrar;
        OSRCleanup();
        swq_op_registrar::DeInitialize();
    }

    CPLDestroyMutex( hDRMutex );
    hDRMutex = NULL;

    CPLFinderClean();
    VSICleanupFileManager();
    CPLFreeConfig();
    CPLCleanupTLS();
}
