_AVCBinWriteArc(AVCRawBinFile *psFile, AVCArc *psArc,
                    int nPrecision, AVCRawBinFile *psIndexFile)
{
    int         i, nRecSize, nCurPos;

    nCurPos = psFile->nCurPos/2;

    AVCRawBinWriteInt32(psFile, psArc->nArcId);
    if (CPLGetLastErrorNo() != 0)
        return -1;


    nRecSize = (6 * 4 + psArc->numVertices*2 *
                ((nPrecision == AVC_SINGLE_PREC)? 4 : 8)) / 2;
    AVCRawBinWriteInt32(psFile, nRecSize);
    AVCRawBinWriteInt32(psFile, psArc->nUserId);
    AVCRawBinWriteInt32(psFile, psArc->nFNode);
    AVCRawBinWriteInt32(psFile, psArc->nTNode);
    AVCRawBinWriteInt32(psFile, psArc->nLPoly);
    AVCRawBinWriteInt32(psFile, psArc->nRPoly);
    AVCRawBinWriteInt32(psFile, psArc->numVertices);

    if (nPrecision == AVC_SINGLE_PREC)
    {
        for(i=0; i<psArc->numVertices; i++)
        {
            AVCRawBinWriteFloat(psFile, (float)psArc->pasVertices[i].x);
            AVCRawBinWriteFloat(psFile, (float)psArc->pasVertices[i].y);
        }
    }
    else
    {
        for(i=0; i<psArc->numVertices; i++)
        {
            AVCRawBinWriteDouble(psFile, psArc->pasVertices[i].x);
            AVCRawBinWriteDouble(psFile, psArc->pasVertices[i].y);
        }

    }


    if (psIndexFile)
    {
        _AVCBinWriteIndexEntry(psIndexFile, nCurPos, nRecSize);
    }

    if (CPLGetLastErrorNo() != 0)
        return -1;

    return 0;
}
