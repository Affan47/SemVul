GetProjectionRef()

{

    const char* pszPrj = GDALPamDataset::GetProjectionRef();
    if(pszPrj && strlen(pszPrj) > 0)
        return pszPrj;

    return pszProjection;
}
