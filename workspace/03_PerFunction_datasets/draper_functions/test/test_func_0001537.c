ClearRawLink()

{
    if( poRawRaster != NULL )
    {
        VSILFILE* fp = poRawRaster->GetFPL();
        delete poRawRaster;
        poRawRaster = NULL;


        if( fp != NULL )
        {
            CPLCloseShared( (FILE*) fp );
        }
    }
    CPLFree( pszSourceFilename );
    pszSourceFilename = NULL;
}
