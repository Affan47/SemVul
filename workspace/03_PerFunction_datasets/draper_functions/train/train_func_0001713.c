SetStatistics( double dfMin, double dfMax, double dfMean, double dfStdDev )
{

    if( dfMin == this->dfMin
        && dfMax == this->dfMax
        && dfMean == this->dfMean
        && dfStdDev == this->dfStdDev )
        return CE_None;

    this->dfMin = dfMin;
    this->dfMax = dfMax;
    this->dfMean = dfMean;
    this->dfStdDev = dfStdDev;


    minmaxmeanstddev = HAS_ALL_FLAGS;

    EHdrDataset* poEDS = (EHdrDataset *) poDS;

    if( poEDS->RewriteSTX() != CE_None )
        return RawRasterBand::SetStatistics( dfMin, dfMax, dfMean, dfStdDev );
    else
        return CE_None;
}
