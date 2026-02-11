IWriteBlock(int nBlockXOff, int nBlockYOff, void* pImage)
{
    SRTMHGTDataset* poGDS = (SRTMHGTDataset*) poDS;

    CPLAssert(nBlockXOff == 0);
    if(nBlockXOff != 0)
    {
        CPLError(CE_Failure, CPLE_NotSupported, "unhandled nBlockXOff value : %d", nBlockXOff);
        return CE_Failure;
    }

    if((poGDS == NULL) || (poGDS->fpImage == NULL) || (poGDS->eAccess != GA_Update))
        return CE_Failure;

    VSIFSeekL(poGDS->fpImage, nBlockYOff*nBlockXSize*2, SEEK_SET);

#ifdef CPL_LSB
    memcpy(poGDS->panBuffer, pImage, nBlockXSize*sizeof(GInt16));
    GDALSwapWords(poGDS->panBuffer, 2, nBlockXSize, 2);
    VSIFWriteL((unsigned char*)poGDS->panBuffer, nBlockXSize, 2, poGDS->fpImage);
#else
    VSIFWriteL((unsigned char*)pImage, nBlockXSize, 2, poGDS->fpImage);
#endif

    return CE_None;
}
