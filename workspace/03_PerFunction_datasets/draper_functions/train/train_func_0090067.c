GetFileList()
{
    CPLString osPath = CPLGetPath( GetDescription() );
    CPLString osName = CPLGetBasename( GetDescription() );
    CPLString osHDRFilename;

    char **papszFileList = NULL;


    papszFileList = GDALPamDataset::GetFileList();


    osHDRFilename = CPLFormCIFilename( osPath, osName, ".sgrd" );
    papszFileList = CSLAddString( papszFileList, osHDRFilename );

    return papszFileList;
}
