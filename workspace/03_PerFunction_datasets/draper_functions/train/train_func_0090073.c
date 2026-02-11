AVCBinWriteClose(AVCBinFile *psFile)
{
    if (psFile->eFileType == AVCFileTABLE)
    {
        _AVCBinWriteCloseTable(psFile);
        return;
    }


    if (psFile->psRawBinFile &&
        (psFile->eFileType == AVCFileARC ||
         psFile->eFileType == AVCFilePAL ||
         psFile->eFileType == AVCFileRPL ||
         psFile->eFileType == AVCFileLAB ||
         psFile->eFileType == AVCFileCNT ||
         psFile->eFileType == AVCFileTXT ||
         psFile->eFileType == AVCFileTX6 ||
         (psFile->eFileType == AVCFileTOL &&
          psFile->nPrecision == AVC_DOUBLE_PREC) ) )
    {
        GInt32 n32Size;
        n32Size = psFile->psRawBinFile->nCurPos/2;

        if (psFile->eCoverType == AVCCoverPC)
        {


            n32Size -= 128;

            if (psFile->psRawBinFile->nCurPos%512 != 0)
                AVCRawBinWriteZeros(psFile->psRawBinFile,
                                    512 - psFile->psRawBinFile->nCurPos%512);

            VSIFSeek(psFile->psRawBinFile->fp, 2, SEEK_SET);
            AVCRawBinWriteInt32(psFile->psRawBinFile, n32Size);

            VSIFSeek(psFile->psRawBinFile->fp, 256+24, SEEK_SET);
            AVCRawBinWriteInt32(psFile->psRawBinFile, n32Size);
        }
        else
        {

            VSIFSeek(psFile->psRawBinFile->fp, 24, SEEK_SET);
            AVCRawBinWriteInt32(psFile->psRawBinFile, n32Size);
        }
    }

    AVCRawBinClose(psFile->psRawBinFile);
    psFile->psRawBinFile = NULL;


    if (psFile->psIndexFile)
    {
        GInt32 n32Size;
        n32Size = psFile->psIndexFile->nCurPos/2;

        if (psFile->eCoverType == AVCCoverPC)
        {


            n32Size -= 128;

            if (psFile->psIndexFile->nCurPos%512 != 0)
                AVCRawBinWriteZeros(psFile->psIndexFile,
                                    512 - psFile->psIndexFile->nCurPos%512);

            VSIFSeek(psFile->psIndexFile->fp, 2, SEEK_SET);
            AVCRawBinWriteInt32(psFile->psIndexFile, n32Size);

            VSIFSeek(psFile->psIndexFile->fp, 256+24, SEEK_SET);
            AVCRawBinWriteInt32(psFile->psIndexFile, n32Size);
        }
        else
        {

            VSIFSeek(psFile->psIndexFile->fp, 24, SEEK_SET);
            AVCRawBinWriteInt32(psFile->psIndexFile, n32Size);
        }

        AVCRawBinClose(psFile->psIndexFile);
        psFile->psIndexFile = NULL;
    }

    CPLFree(psFile->pszFilename);

    CPLFree(psFile);
}
