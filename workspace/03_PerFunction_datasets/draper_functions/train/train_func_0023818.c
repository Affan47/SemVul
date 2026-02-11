ProcessStatsFile()
{
    VSILFILE	*fpStaFile;

    osStaFilename = CPLResetExtension( pszHDRFilename, "sta" );
    fpStaFile = VSIFOpenL( osStaFilename, "rb" );

    if (!fpStaFile)
    {
        osStaFilename = "";
        return;
    }

    int lTestHeader[10],lOffset;

    if( VSIFReadL( lTestHeader, sizeof(int), 10, fpStaFile ) != 10 )
    {
        VSIFCloseL( fpStaFile );
        osStaFilename = "";
        return;
    }

    int isFloat;
    isFloat = (byteSwapInt(lTestHeader[0]) == 1111838282);

    int nb,i;
    float * fStats;
    double * dStats, dMin, dMax, dMean, dStd;

    nb=byteSwapInt(lTestHeader[3]);

    if (nb < 0 || nb > nBands)
    {
        CPLDebug("ENVI", ".sta file has statistics for %d bands, "
                         "whereas the dataset has only %d bands", nb, nBands);
        nb = nBands;
    }

    VSIFSeekL(fpStaFile,40+(nb+1)*4,SEEK_SET);

    if (VSIFReadL(&lOffset,sizeof(int),1,fpStaFile) == 1)
    {
        VSIFSeekL(fpStaFile,40+(nb+1)*8+byteSwapInt(lOffset)+nb,SEEK_SET);

        if (isFloat)
        {
            fStats = (float*)CPLCalloc(nb*4,4);
            if ((int)VSIFReadL(fStats,4,nb*4,fpStaFile) == nb*4)
            {
                for (i=0;i<nb;i++)
                {
                    GetRasterBand(i+1)->SetStatistics(
                        byteSwapFloat(fStats[i]),
                        byteSwapFloat(fStats[nb+i]),
                        byteSwapFloat(fStats[2*nb+i]),
                        byteSwapFloat(fStats[3*nb+i]));
                }
            }
            CPLFree(fStats);
        }
        else
        {
            dStats = (double*)CPLCalloc(nb*4,8);
            if ((int)VSIFReadL(dStats,8,nb*4,fpStaFile) == nb*4)
            {
                for (i=0;i<nb;i++)
                {
                    dMin = byteSwapDouble(dStats[i]);
                    dMax = byteSwapDouble(dStats[nb+i]);
                    dMean = byteSwapDouble(dStats[2*nb+i]);
                    dStd = byteSwapDouble(dStats[3*nb+i]);
                    if (dMin != dMax && dStd != 0)
                        GetRasterBand(i+1)->SetStatistics(dMin,dMax,dMean,dStd);
                }
            }
            CPLFree(dStats);
        }
    }
    VSIFCloseL( fpStaFile );
}
