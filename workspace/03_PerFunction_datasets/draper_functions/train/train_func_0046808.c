setCompressionType( const std::string & comp,
                                              int quality = -1 )
    {


        if ( comp == "NONE" )
            tiffcomp = COMPRESSION_NONE;
        else if ( ( comp == "JPEG" ) && ( quality != -1 ) )
            tiffcomp = COMPRESSION_OJPEG;
        else if ( comp == "RLE" || comp == "RunLength")
            tiffcomp = COMPRESSION_CCITTRLE;
        else if ( comp == "PACKBITS")
            tiffcomp = COMPRESSION_PACKBITS;
        else if ( comp == "LZW" )
            tiffcomp = COMPRESSION_LZW;
        else if ( comp == "DEFLATE" )
            tiffcomp = COMPRESSION_DEFLATE;
    }
