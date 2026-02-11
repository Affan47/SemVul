Open( GDALOpenInfo * poOpenInfo )

{
    char *pszVRTPath = NULL;


    if( !Identify( poOpenInfo ) )
        return NULL;


    char        *pszXML;

    VSILFILE        *fp = VSIFOpenL(poOpenInfo->pszFilename, "rb");
    if( fp != NULL )
    {
        unsigned int nLength;

        VSIFSeekL( fp, 0, SEEK_END );
        nLength = (int) VSIFTellL( fp );
        VSIFSeekL( fp, 0, SEEK_SET );

        nLength = MAX(0,nLength);
        pszXML = (char *) VSIMalloc(nLength+1);

        if( pszXML == NULL )
        {
            VSIFCloseL(fp);
            CPLError( CE_Failure, CPLE_OutOfMemory,
                      "Failed to allocate %d byte buffer to hold VRT xml file.",
                      nLength );
            return NULL;
        }

        if( VSIFReadL( pszXML, 1, nLength, fp ) != nLength )
        {
            VSIFCloseL(fp);
            CPLFree( pszXML );
            CPLError( CE_Failure, CPLE_FileIO,
                      "Failed to read %d bytes from VRT xml file.",
                      nLength );
            return NULL;
        }

        pszXML[nLength] = '\0';

        char* pszCurDir = CPLGetCurrentDir();
        const char *currentVrtFilename = CPLProjectRelativeFilename(pszCurDir, poOpenInfo->pszFilename);
        CPLFree(pszCurDir);
#if defined(HAVE_READLINK) && defined(HAVE_LSTAT)
        VSIStatBuf statBuffer;
        char filenameBuffer[2048];

        while( true ) {
            int lstatCode = lstat( currentVrtFilename, &statBuffer );
            if ( lstatCode == -1 ) {
                if (errno == ENOENT) {

                    break;
                } else {
                    VSIFCloseL(fp);
                    CPLFree( pszXML );
                    CPLError( CE_Failure, CPLE_FileIO,
                              "Failed to lstat %s: %s",
                              currentVrtFilename,
                              VSIStrerror(errno) );
                    return NULL;
                }
            }

            if ( !VSI_ISLNK(statBuffer.st_mode) ) {
                break;
            }

            int bufferSize = readlink(currentVrtFilename, filenameBuffer, sizeof(filenameBuffer));
            if (bufferSize != -1) {
                filenameBuffer[MIN(bufferSize, (int) sizeof(filenameBuffer) - 1)] = 0;

                currentVrtFilename = CPLProjectRelativeFilename(CPLGetDirname(currentVrtFilename), filenameBuffer);
            } else {
                VSIFCloseL(fp);
                CPLFree( pszXML );
                CPLError( CE_Failure, CPLE_FileIO,
                          "Failed to read filename from symlink %s: %s",
                          currentVrtFilename,
                          VSIStrerror(errno) );
                return NULL;
            }
        }
#endif

        pszVRTPath = CPLStrdup(CPLGetPath(currentVrtFilename));

        VSIFCloseL(fp);
    }


    else
    {
        pszXML = CPLStrdup( poOpenInfo->pszFilename );
    }


    VRTDataset *poDS = (VRTDataset *) OpenXML( pszXML, pszVRTPath, poOpenInfo->eAccess );

    if( poDS != NULL )
        poDS->bNeedsFlush = FALSE;

    CPLFree( pszXML );
    CPLFree( pszVRTPath );


    if( fp != NULL && poDS != NULL )
        poDS->oOvManager.Initialize( poDS, poOpenInfo->pszFilename );

    return poDS;
}
