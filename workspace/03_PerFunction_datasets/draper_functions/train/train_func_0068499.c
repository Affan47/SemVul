TIFF_next( FL_IMAGE * im )
{
    SPEC *sp = im->io_spec;

    read_tiff_ifd( im->fpin, sp );

    if ( get_image_info_from_ifd( im ) < 0 )
    {
        flimage_error( im, "Can't get image info" );
        M_err( "Next", "Can't get image info" );
        return -1;
    }

    flimage_getmem( im );

    return TIFF_readpixels( im );
}
