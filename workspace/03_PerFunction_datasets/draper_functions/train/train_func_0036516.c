RewriteSTX()
{
    CPLString osPath = CPLGetPath( GetDescription() );
    CPLString osName = CPLGetBasename( GetDescription() );
    CPLString osSTXFilename = CPLFormCIFilename( osPath, osName, "stx" );


    VSILFILE	*fp;
    fp = VSIFOpenL( osSTXFilename, "wt" );
    if( fp == NULL )
    {
        CPLDebug( "EHDR", "Failed to rewrite .stx file %s.",
                  osSTXFilename.c_str() );
        return CE_Failure;
    }

    for (int i = 0; i < nBands; ++i)
    {
        EHdrRasterBand* poBand = (EHdrRasterBand*)papoBands[i];
        VSIFPrintfL( fp, "%d %.10f %.10f ", i+1, poBand->dfMin, poBand->dfMax );
        if ( poBand->minmaxmeanstddev & HAS_MEAN_FLAG )
            VSIFPrintfL( fp, "%.10f ", poBand->dfMean);
        else
            VSIFPrintfL( fp, "# ");

        if ( poBand->minmaxmeanstddev & HAS_STDDEV_FLAG )
            VSIFPrintfL( fp, "%.10f\n", poBand->dfStdDev);
        else
            VSIFPrintfL( fp, "#\n");
    }

    VSIFCloseL( fp );

    return CE_None;
}
