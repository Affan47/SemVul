IReadBlock( int nBlockXOff, int nBlockYOff,
                                  void * pImage )

{
    BLXDataset *poGDS = (BLXDataset *) poDS;

    if(blx_readcell(poGDS->blxcontext, nBlockYOff, nBlockXOff, (short *)pImage, nBlockXSize*nBlockYSize*2, overviewLevel) == NULL) {
	CPLError(CE_Failure, CPLE_AppDefined,
		 "Failed to read BLX cell");
	return CE_Failure;
    }

    return CE_None;
}
