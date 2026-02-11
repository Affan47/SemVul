DumpHeader(AVCRawBinFile *hFile)
{
    AVCBinHeader sHdr;
    int          nStatus;

    nStatus = _AVCBinReadHeader(hFile, &sHdr);

    if (nStatus == 0)
    {
        printf("\nFile Header:\n");
        printf("  Signature:  0x%8.8x (%d)\n", sHdr.nSignature,
                                               sHdr.nSignature);
        printf("  Precision:  0x%8.8x (%d)\n", sHdr.nPrecision,
                                               sHdr.nPrecision);
        printf("  Length:     0x%8.8x (%d)\n", sHdr.nLength,
                                               sHdr.nLength);
        printf("\n");
    }

    if (sHdr.nPrecision < 0 || sHdr.nPrecision > 1000)
        return AVC_DOUBLE_PREC;
    else
        return AVC_SINGLE_PREC;

}
