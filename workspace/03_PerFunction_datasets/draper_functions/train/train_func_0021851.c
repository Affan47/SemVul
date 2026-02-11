GDALPipeWrite(GDALPipe* p, int nGCPCount, const GDAL_GCP* pasGCPs)
{
    if( !GDALPipeWrite(p, nGCPCount ) )
        return FALSE;
    for(int i=0;i<nGCPCount;i++)
    {
        if( !GDALPipeWrite(p, pasGCPs[i].pszId) ||
            !GDALPipeWrite(p, pasGCPs[i].pszInfo) ||
            !GDALPipeWrite(p, pasGCPs[i].dfGCPPixel) ||
            !GDALPipeWrite(p, pasGCPs[i].dfGCPLine) ||
            !GDALPipeWrite(p, pasGCPs[i].dfGCPX) ||
            !GDALPipeWrite(p, pasGCPs[i].dfGCPY) ||
            !GDALPipeWrite(p, pasGCPs[i].dfGCPZ) )
            return FALSE;
    }
    return TRUE;
}
