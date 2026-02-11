AVCRawBinEOF(AVCRawBinFile *psFile)
{
    if (psFile == NULL || psFile->fp == NULL)
        return TRUE;


    if (psFile->eAccess != AVCRead && psFile->eAccess != AVCReadWrite)
        return TRUE;


    if (psFile->nFileDataSize > 0 &&
        (psFile->nOffset+psFile->nCurPos) >= psFile->nFileDataSize)
        return TRUE;


    if ((psFile->nCurPos == 0 && psFile->nCurSize == 0) ||
        (psFile->nCurPos == AVCRAWBIN_READBUFSIZE &&
         psFile->nCurSize == AVCRAWBIN_READBUFSIZE))
    {
        GByte c;


        bDisableReadBytesEOFError = TRUE;
        AVCRawBinReadBytes(psFile, 1, &c);
        bDisableReadBytesEOFError = FALSE;

        if (psFile->nCurPos > 0)
            AVCRawBinFSeek(psFile, -1, SEEK_CUR);
    }

    return (psFile->nCurPos == psFile->nCurSize &&
            VSIFEof(psFile->fp));
}
