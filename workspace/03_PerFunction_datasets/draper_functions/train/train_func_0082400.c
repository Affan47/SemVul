GTIFFGetCompressionMethod(const char* pszValue, const char* pszVariableName)
{
    int nCompression = COMPRESSION_NONE;
    if( EQUAL( pszValue, "NONE" ) )
        nCompression = COMPRESSION_NONE;
    else if( EQUAL( pszValue, "JPEG" ) )
        nCompression = COMPRESSION_JPEG;
    else if( EQUAL( pszValue, "LZW" ) )
        nCompression = COMPRESSION_LZW;
    else if( EQUAL( pszValue, "PACKBITS" ))
        nCompression = COMPRESSION_PACKBITS;
    else if( EQUAL( pszValue, "DEFLATE" ) || EQUAL( pszValue, "ZIP" ))
        nCompression = COMPRESSION_ADOBE_DEFLATE;
    else if( EQUAL( pszValue, "FAX3" )
                || EQUAL( pszValue, "CCITTFAX3" ))
        nCompression = COMPRESSION_CCITTFAX3;
    else if( EQUAL( pszValue, "FAX4" )
                || EQUAL( pszValue, "CCITTFAX4" ))
        nCompression = COMPRESSION_CCITTFAX4;
    else if( EQUAL( pszValue, "CCITTRLE" ) )
        nCompression = COMPRESSION_CCITTRLE;
    else if( EQUAL( pszValue, "LZMA" ) )
        nCompression = COMPRESSION_LZMA;
    else
        CPLError( CE_Warning, CPLE_IllegalArg,
                    "%s=%s value not recognised, ignoring.",
                    pszVariableName,pszValue );

#if defined(TIFFLIB_VERSION) && TIFFLIB_VERSION > 20031007
    if (nCompression != COMPRESSION_NONE &&
        !TIFFIsCODECConfigured((uint16) nCompression))
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                "Cannot create TIFF file due to missing codec for %s.", pszValue );
        return -1;
    }
#endif

    return nCompression;
}
