GDALDumpOpenDatasetsForeach(void* elt, void* user_data)
{
    DatasetCtxt* psStruct = (DatasetCtxt*) elt;
    FILE *fp = (FILE*) user_data;
    const char *pszDriverName;
    GDALDataset *poDS = psStruct->poDS;


    if (poDS->GetShared())
        return TRUE;

    if( poDS->GetDriver() == NULL )
        pszDriverName = "DriverIsNULL";
    else
        pszDriverName = poDS->GetDriver()->GetDescription();

    poDS->Reference();
    VSIFPrintf( fp, "  %d %c %-6s %7d %dx%dx%d %s\n",
                poDS->Dereference(),
                poDS->GetShared() ? 'S' : 'N',
                pszDriverName,
                -1,
                poDS->GetRasterXSize(),
                poDS->GetRasterYSize(),
                poDS->GetRasterCount(),
                poDS->GetDescription() );

    return TRUE;
}
