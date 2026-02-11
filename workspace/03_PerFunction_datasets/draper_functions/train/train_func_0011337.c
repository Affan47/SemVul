_AVCBinWriteArcNit(AVCRawBinFile *psFile, AVCFieldInfo *psField)
{


    AVCRawBinWritePaddedString(psFile, 16, psField->szName);
    if (CPLGetLastErrorNo() != 0)
        return -1;

    AVCRawBinWriteInt16(psFile, psField->nSize);
    AVCRawBinWriteInt16(psFile, psField->v2);
    AVCRawBinWriteInt16(psFile, psField->nOffset);
    AVCRawBinWriteInt16(psFile, psField->v4);
    AVCRawBinWriteInt16(psFile, psField->v5);
    AVCRawBinWriteInt16(psFile, psField->nFmtWidth);
    AVCRawBinWriteInt16(psFile, psField->nFmtPrec);
    AVCRawBinWriteInt16(psFile, psField->nType1);
    AVCRawBinWriteInt16(psFile, psField->nType2);
    AVCRawBinWriteInt16(psFile, psField->v10);
    AVCRawBinWriteInt16(psFile, psField->v11);
    AVCRawBinWriteInt16(psFile, psField->v12);
    AVCRawBinWriteInt16(psFile, psField->v13);

    AVCRawBinWritePaddedString(psFile, 16, psField->szAltName);

    AVCRawBinWriteZeros(psFile, 56);

    AVCRawBinWriteInt16(psFile, psField->nIndex);

    AVCRawBinWriteZeros(psFile, 28);

    if (CPLGetLastErrorNo() != 0)
        return -1;

    return 0;
}
