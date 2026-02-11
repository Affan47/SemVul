_AVCBinWriteCloseTable(AVCBinFile *psFile)
{
    if (psFile->eFileType != AVCFileTABLE)
        return;


    if (psFile->hDBFFile)
    {


        DBFClose(psFile->hDBFFile);
        psFile->hDBFFile = NULL;
    }
    else if (psFile->psRawBinFile)
    {


        AVCRawBinClose(psFile->psRawBinFile);
        psFile->psRawBinFile = NULL;
    }


    _AVCDestroyTableDef(psFile->hdr.psTableDef);

    CPLFree(psFile->pszFilename);

    CPLFree(psFile);
}
