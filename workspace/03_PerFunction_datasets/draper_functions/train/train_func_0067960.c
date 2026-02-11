_AVCBinWriteCnt(AVCRawBinFile *psFile, AVCCnt *psCnt,
                              int nPrecision, AVCRawBinFile *psIndexFile)
{
    int i, nRecSize, nCurPos;

    nCurPos = psFile->nCurPos/2;

    AVCRawBinWriteInt32(psFile, psCnt->nPolyId);
    if (CPLGetLastErrorNo() != 0)
        return -1;


    nRecSize = ( 4 + psCnt->numLabels * 4 +
                 2 * ((nPrecision == AVC_SINGLE_PREC)? 4 : 8)) / 2;

    AVCRawBinWriteInt32(psFile, nRecSize);

    if (nPrecision == AVC_SINGLE_PREC)
    {
        AVCRawBinWriteFloat(psFile, (float)psCnt->sCoord.x);
        AVCRawBinWriteFloat(psFile, (float)psCnt->sCoord.y);
    }
    else
    {
        AVCRawBinWriteDouble(psFile, psCnt->sCoord.x);
        AVCRawBinWriteDouble(psFile, psCnt->sCoord.y);
    }

    AVCRawBinWriteInt32(psFile, psCnt->numLabels);

    for(i=0; i<psCnt->numLabels; i++)
    {
        AVCRawBinWriteInt32(psFile, psCnt->panLabelIds[i]);
    }


    if (psIndexFile)
    {
        _AVCBinWriteIndexEntry(psIndexFile, nCurPos, nRecSize);
    }

    if (CPLGetLastErrorNo() != 0)
        return -1;

    return 0;
}
