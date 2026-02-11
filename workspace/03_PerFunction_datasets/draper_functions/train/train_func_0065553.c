Open( std::string filename, std::string access ) const

{
    VSILFILE *fp = VSIFOpenL( filename.c_str(), access.c_str() );

    if( fp == NULL )
        ThrowPCIDSKException( "Failed to open %s: %s",
                              filename.c_str(), LastError() );

    return fp;
}
