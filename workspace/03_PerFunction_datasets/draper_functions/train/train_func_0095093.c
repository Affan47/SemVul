AVCRawBinWriteDouble(AVCRawBinFile *psFile, double dValue)
{
    if (psFile->eByteOrder != geSystemByteOrder)
    {
        CPL_SWAPDOUBLE(&dValue);
    }

    AVCRawBinWriteBytes(psFile, 8, (GByte*)&dValue);
}
