FlushMemoryResult()

{
    if( strlen(osResultFilename) > 0 )
    {
        VSIUnlink( osResultFilename );
        osResultFilename = "";
    }

    if( pabySavedDataBuffer )
    {
        CPLFree( pabySavedDataBuffer );
        pabySavedDataBuffer = NULL;
    }
}
