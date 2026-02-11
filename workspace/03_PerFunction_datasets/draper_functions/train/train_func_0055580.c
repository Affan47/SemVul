IWriteBlock( int nBlockXOff, int nBlockYOff,
                                     void * pImage )

{
    CPLErr eErr;
    VRTWarpedDataset *poWDS = (VRTWarpedDataset *) poDS;


    if (poWDS->poWarper->GetOptions()->nDstAlphaBand == nBand)
    {
        eErr = CE_None;
    }
    else
    {

        eErr = VRTRasterBand::IWriteBlock(nBlockXOff, nBlockYOff, pImage);
    }

    return eErr;
}
