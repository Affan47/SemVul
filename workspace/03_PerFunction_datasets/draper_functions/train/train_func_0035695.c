HFASetRasterBlock( HFAHandle hHFA, int nBand,
                          int nXBlock, int nYBlock, void * pData )

{
    if( nBand < 1 || nBand > hHFA->nBands )
        return CE_Failure;

    return( hHFA->papoBand[nBand-1]->SetRasterBlock(nXBlock,nYBlock,pData) );
}
