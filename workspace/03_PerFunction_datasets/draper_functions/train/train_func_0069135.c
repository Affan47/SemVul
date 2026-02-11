_AVCBinReadNextRxp(AVCRawBinFile *psFile, AVCRxp *psRxp,
                       int nPrecision)
{

    psRxp->n1  = AVCRawBinReadInt32(psFile);
    if (AVCRawBinEOF(psFile))
        return -1;
    psRxp->n2  = AVCRawBinReadInt32(psFile);

    return 0;
}
