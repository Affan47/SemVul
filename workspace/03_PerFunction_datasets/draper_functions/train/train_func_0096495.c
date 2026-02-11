GDALPDFFind4Corners(const GDAL_GCP* pasGCPList,
                         int& iUL, int& iUR, int& iLR, int& iLL)
{
    double dfMeanX = 0, dfMeanY = 0;
    int i;

    iUL = 0;
    iUR = 0;
    iLR = 0;
    iLL = 0;

    for(i = 0; i < 4; i++ )
    {
        dfMeanX += pasGCPList[i].dfGCPPixel;
        dfMeanY += pasGCPList[i].dfGCPLine;
    }
    dfMeanX /= 4;
    dfMeanY /= 4;

    for(i = 0; i < 4; i++ )
    {
        if (pasGCPList[i].dfGCPPixel < dfMeanX &&
            pasGCPList[i].dfGCPLine  < dfMeanY )
            iUL = i;

        else if (pasGCPList[i].dfGCPPixel > dfMeanX &&
                    pasGCPList[i].dfGCPLine  < dfMeanY )
            iUR = i;

        else if (pasGCPList[i].dfGCPPixel > dfMeanX &&
                    pasGCPList[i].dfGCPLine  > dfMeanY )
            iLR = i;

        else if (pasGCPList[i].dfGCPPixel < dfMeanX &&
                    pasGCPList[i].dfGCPLine  > dfMeanY )
            iLL = i;
    }
}
