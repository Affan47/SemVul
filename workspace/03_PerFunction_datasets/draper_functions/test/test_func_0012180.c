GetFileList()

{
    char **papszFileList = NULL;


    papszFileList = GDALPamDataset::GetFileList();

    if( strlen(osSTAFilename) > 0 )
        papszFileList = CSLAddString( papszFileList, osSTAFilename );

    return papszFileList;
}
