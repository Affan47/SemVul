GetMetadataItem( const char * pszName,
                                                     const char * pszDomain )
{
    const char* pszRet = GDALPamRasterBand::GetMetadataItem(pszName, pszDomain);
    if (pszRet)
        return pszRet;

    GDALRasterBand* _poSrcBand = RefUnderlyingRasterBand();
    if (_poSrcBand)
    {
        pszRet = _poSrcBand->GetMetadataItem( pszName, pszDomain );
        UnrefUnderlyingRasterBand(_poSrcBand);
    }

    return pszRet;
}
