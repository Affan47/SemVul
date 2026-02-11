GDALDumpOpenSharedDatasetsForeach(void* elt, void* user_data)
{
    SharedDatasetCtxt* psStruct = (SharedDatasetCtxt*) elt;
    FILE *fp = (FILE*) user_data;
    const char *pszDriverName;
    GDALDataset *poDS = psStruct->poDS;

    if( poDS->GetDriver() == NULL )
        pszDriverName = "DriverIsNULL";
    else
        pszDriverName = poDS->GetDriver()->GetDescription();

    poDS->Reference();
    VSIFPrintf( fp, "  %d %c %-6s %7d %dx%dx%d %s\n",
                poDS->Dereference(),
                poDS->GetShared() ? 'S' : 'N',
                pszDriverName,
                (int)psStruct->nPID,
                poDS->GetRasterXSize(),
                poDS->GetRasterYSize(),
                poDS->GetRasterCount(),
                poDS->GetDescription() );

    return TRUE;
}
