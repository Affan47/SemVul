GDALCreateGCPRefineTransformer( int nGCPCount, const GDAL_GCP *pasGCPList,
                                int nReqOrder, int bReversed, double dfTolerance, int nMinimumGcps)

{

    if(nMinimumGcps == -1)
    {
        nMinimumGcps = ((nReqOrder+1) * (nReqOrder+2)) / 2 + 1;
    }
    return GDALCreateGCPTransformerEx(nGCPCount, pasGCPList, nReqOrder, bReversed, TRUE, dfTolerance, nMinimumGcps);
}
