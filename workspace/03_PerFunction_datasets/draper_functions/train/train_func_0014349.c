Stat( const char * pszFilename,
                                       VSIStatBufL * psStatBuf,
                                       int nFlags )

{
    CPLString osSubFilePath;
    vsi_l_offset nOff, nSize;

    memset( psStatBuf, 0, sizeof(VSIStatBufL) );

    if( !DecomposePath( pszFilename, osSubFilePath, nOff, nSize ) )
    {
        errno = ENOENT;
        return -1;
    }

    int nResult = VSIStatExL( osSubFilePath, psStatBuf, nFlags );

    if( nResult == 0 )
    {
        if( nSize != 0 )
            psStatBuf->st_size = (long)nSize;
        else
            psStatBuf->st_size -= (long)nOff;
    }

    return nResult;
}
