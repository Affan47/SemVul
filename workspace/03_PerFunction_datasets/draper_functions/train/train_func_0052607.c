_AVCBinReadHeader(AVCRawBinFile *psFile, AVCBinHeader *psHeader,
                      AVCCoverType eCoverType)
{
    int nStatus = 0;


    if (eCoverType == AVCCoverPC)
        AVCRawBinFSeek(psFile, 256, SEEK_SET);
    else
        AVCRawBinFSeek(psFile, 0, SEEK_SET);

    psHeader->nSignature = AVCRawBinReadInt32(psFile);

    if (AVCRawBinEOF(psFile))
        nStatus = -1;

    psHeader->nPrecision = AVCRawBinReadInt32(psFile);
    psHeader->nRecordSize= AVCRawBinReadInt32(psFile);


    AVCRawBinFSeek(psFile, 12, SEEK_CUR);
    psHeader->nLength    = AVCRawBinReadInt32(psFile);


    if (eCoverType == AVCCoverPC)
        AVCRawBinSetFileDataSize(psFile, psHeader->nLength*2 + 256);
    else
        AVCRawBinSetFileDataSize(psFile, psHeader->nLength*2 );


    AVCRawBinFSeek(psFile, 72, SEEK_CUR);

    return nStatus;
}
