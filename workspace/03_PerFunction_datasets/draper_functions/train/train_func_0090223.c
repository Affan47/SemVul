finalize()
    {
        VIGRA_IMPEX_FINALIZED(finalized);


        bands.resize( width * components );
        finalized = true;


        info.image_width = width;
        info.image_height = height;
        info.input_components = components;


        info.in_color_space = components == 1 ? JCS_GRAYSCALE : JCS_RGB;
        info.X_density = 100;
        info.Y_density = 100;


        if (setjmp(err.buf))
            vigra_fail( "error in jpeg_set_defaults()" );
        jpeg_set_defaults(&info);


        if ( quality != -1 ) {
            if (setjmp(err.buf))
                vigra_fail( "error in jpeg_set_quality()" );
            jpeg_set_quality( &info, quality, TRUE );
        }


        for ( unsigned int i = 0; i < MAX_COMPONENTS; ++i ) {
            info.comp_info[i].h_samp_factor = 1;
            info.comp_info[i].v_samp_factor = 1;
        }
#ifdef ENTROPY_OPT_SUPPORTED
        info.optimize_coding = TRUE;
#endif
        info.dct_method = JDCT_FLOAT;


        if (setjmp(err.buf))
            vigra_fail( "error in jpeg_start_compress()" );
        jpeg_start_compress( &info, TRUE );

        if (iccProfile.size()) {
            write_icc_profile(&info, iccProfile.begin(), (unsigned int)iccProfile.size());
        }
    }
