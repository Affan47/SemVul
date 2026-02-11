LoadEXIFMetadata()
{
    if (bEXIFMetadataLoaded)
        return;
    bEXIFMetadataLoaded = TRUE;

    if (!SetDirectory())
        return;

    VSILFILE* fp = (VSILFILE*) TIFFClientdata( hTIFF );

    GByte          abyHeader[2];
    VSIFSeekL(fp, 0, SEEK_SET);
    VSIFReadL(abyHeader, 1, 2, fp);

    int bLittleEndian = abyHeader[0] == 'I' && abyHeader[1] == 'I';
    int bSwabflag = bLittleEndian ^ CPL_IS_LSB;

    char** papszMetadata = NULL;
    toff_t nOffset;

    if (TIFFGetField(hTIFF, TIFFTAG_EXIFIFD, &nOffset))
    {
        int nExifOffset = (int)nOffset, nInterOffset = 0, nGPSOffset = 0;
        EXIFExtractMetadata(papszMetadata,
                            fp, (int)nOffset,
                            bSwabflag, 0,
                            nExifOffset, nInterOffset, nGPSOffset);
    }

    if (TIFFGetField(hTIFF, TIFFTAG_GPSIFD, &nOffset))
    {
        int nExifOffset = 0, nInterOffset = 0, nGPSOffset = (int)nOffset;
        EXIFExtractMetadata(papszMetadata,
                            fp, (int)nOffset,
                            bSwabflag, 0,
                            nExifOffset, nInterOffset, nGPSOffset);
    }

    oGTiffMDMD.SetMetadata( papszMetadata, "EXIF" );
    CSLDestroy( papszMetadata );
}
