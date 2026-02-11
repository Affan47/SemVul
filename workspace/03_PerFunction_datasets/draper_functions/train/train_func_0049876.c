read_descriptor_block( FL_IMAGE * im )
{
    int local_map,
        inbyte;
    FILE *fp = im->fpin;
    SPEC *sp = im->io_spec;


    if ( skip_extension( fp, im ) != IMAGESEP )
    {
        flimage_error( im, "%s: no separator or BadBlockMarker", im->infile );
        return -1;
    }


    im->wx = fli_fget2LSBF( fp );
    im->wy = fli_fget2LSBF( fp );


    im->w = fli_fget2LSBF( fp );
    im->h = fli_fget2LSBF( fp );

    if ( sp->lsx < im->w || sp->lsy < im->h )
    {
        M_info( "", "Bad screen description. LX=%d W=%d LY=%d H=%d",
                sp->lsx, im->w, sp->lsy, im->h );
        sp->lsx = im->w;
        sp->lsy = im->h;
    }

    inbyte = getc( fp );
    sp->interlace = ( inbyte & 0x40 ) != 0;
    local_map = ( inbyte & 0x80 );

    if ( ! sp->globalmap && !local_map )
    {
        M_err( "GIFDescriptor", "%s: No ColorMap", im->infile );

    }


    if ( local_map )
    {
        local_map = ( inbyte & 0x07 ) + 1;
        im->map_len = 1 << local_map;
        flimage_getcolormap( im );
        read_map( im );
    }


    if ( sp->gc.tran && sp->gc.tran_col < im->map_len )
        im->tran_index = sp->gc.tran_col;

    if ( im->setup->header_info )
        generate_header_info( im );

    return 0;
}
