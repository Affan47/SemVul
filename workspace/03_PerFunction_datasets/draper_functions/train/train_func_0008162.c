setCompressionType( const std::string & comp,
                                          int quality )
    {
        VIGRA_IMPEX_FINALIZED(pimpl->finalized);
        if ( comp == "LOSSLESS" )
            vigra_fail( "lossless encoding is not supported by your jpeg library." );
        if ( comp == "JPEG_ARITH" )
#ifdef C_ARITH_CODING_SUPPORTED
            pimpl->info.arith_code = TRUE;
#else
            vigra_fail( "arithmetic encoding is not supported by your jpeg library." );
#endif
        pimpl->quality = quality;
    }
