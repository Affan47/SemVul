GetImageRepFilename(const char* pszFilename)
{
    VSIStatBufL sStatBuf;

    CPLString osPath = CPLGetPath( pszFilename );
    CPLString osName = CPLGetBasename( pszFilename );
    CPLString osREPFilename =
        CPLFormCIFilename( osPath, osName, "rep" );
    if( VSIStatExL( osREPFilename.c_str(), &sStatBuf, VSI_STAT_EXISTS_FLAG ) == 0 )
        return osREPFilename;

    if (EQUAL(CPLGetFilename(pszFilename), "imspatio.bil") ||
        EQUAL(CPLGetFilename(pszFilename), "haspatio.bil"))
    {
        CPLString osImageRepFilename(CPLFormCIFilename( osPath, "image", "rep" ));
        if( VSIStatExL( osImageRepFilename.c_str(), &sStatBuf, VSI_STAT_EXISTS_FLAG ) == 0 )
            return osImageRepFilename;


        CPLString dirName(CPLGetDirname(osPath));
        if (CPLIsFilenameRelative(osPath.c_str()))
        {
            char* cwd = CPLGetCurrentDir();
            if (cwd)
            {
                dirName = CPLFormFilename(cwd, dirName.c_str(), NULL);
                CPLFree(cwd);
            }
        }
        while (dirName[0] != 0 && EQUAL(dirName, ".") == FALSE && EQUAL(dirName, "/") == FALSE)
        {
            osImageRepFilename = CPLFormCIFilename( dirName.c_str(), "image", "rep" );
            if( VSIStatExL( osImageRepFilename.c_str(), &sStatBuf, VSI_STAT_EXISTS_FLAG ) == 0 )
                return osImageRepFilename;


            if (EQUAL(dirName, "image"))
            {
                break;
            }
            dirName = CPLString(CPLGetDirname(dirName));
        }
    }
    return CPLString();
}
