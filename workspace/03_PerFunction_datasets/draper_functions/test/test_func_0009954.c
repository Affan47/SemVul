_AVCBinReadNextPal(AVCRawBinFile *psFile, AVCPal *psPal,
                              int nPrecision)
{
    int i, numArcs;
    int nRecordSize, nStartPos, nBytesRead;

    psPal->nPolyId = AVCRawBinReadInt32(psFile);
    nRecordSize    = AVCRawBinReadInt32(psFile) * 2;
    nStartPos      = psFile->nCurPos+psFile->nOffset;

    if (AVCRawBinEOF(psFile))
        return -1;

    if (nPrecision == AVC_SINGLE_PREC)
    {
        psPal->sMin.x  = AVCRawBinReadFloat(psFile);
        psPal->sMin.y  = AVCRawBinReadFloat(psFile);
        psPal->sMax.x  = AVCRawBinReadFloat(psFile);
        psPal->sMax.y  = AVCRawBinReadFloat(psFile);
    }
    else
    {
        psPal->sMin.x  = AVCRawBinReadDouble(psFile);
        psPal->sMin.y  = AVCRawBinReadDouble(psFile);
        psPal->sMax.x  = AVCRawBinReadDouble(psFile);
        psPal->sMax.y  = AVCRawBinReadDouble(psFile);
    }

    numArcs            = AVCRawBinReadInt32(psFile);


    if (psPal->pasArcs == NULL || numArcs > psPal->numArcs)
        psPal->pasArcs = (AVCPalArc*)CPLRealloc(psPal->pasArcs,
                                                 numArcs*sizeof(AVCPalArc));

    psPal->numArcs = numArcs;

    for(i=0; i<numArcs; i++)
    {
        psPal->pasArcs[i].nArcId = AVCRawBinReadInt32(psFile);
        psPal->pasArcs[i].nFNode = AVCRawBinReadInt32(psFile);
        psPal->pasArcs[i].nAdjPoly = AVCRawBinReadInt32(psFile);
    }


    nBytesRead = (psFile->nCurPos + psFile->nOffset) - nStartPos;
    if ( nBytesRead < nRecordSize)
        AVCRawBinFSeek(psFile, nRecordSize - nBytesRead, SEEK_CUR);

    return 0;
}
