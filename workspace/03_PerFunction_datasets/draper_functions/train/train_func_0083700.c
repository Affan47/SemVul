currentScanlineOfBand( unsigned int band )
    {
        const unsigned int row_stride = pimpl->width * pimpl->components;
        if ( pimpl->pixeltype == "UINT8" ) {
            typedef void_vector< UInt8 > bands_type;
            bands_type & bands
                = static_cast< bands_type & >(pimpl->bands);
            return bands.data() + pimpl->scanline * row_stride + band;
        } else if ( pimpl->pixeltype == "UINT16" ) {
            typedef void_vector<UInt16> bands_type;
            bands_type & bands
                = static_cast< bands_type & >(pimpl->bands);
            return bands.data() + pimpl->scanline * row_stride + band;
        } else if ( pimpl->pixeltype == "UINT32" ) {
            typedef void_vector<UInt32> bands_type;
            bands_type & bands
                = static_cast< bands_type & >(pimpl->bands);
            return bands.data() + pimpl->scanline * row_stride + band;
        }
        vigra_postcondition( false, "internal error" );
        return 0;
    }
