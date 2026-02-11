process_lzw_code( FL_IMAGE * im,
                  int        code )
{
    int incode;
    static unsigned char firstchar;
    static unsigned char stack[ MC_SIZE ];
    static int avail,
               oldcode;
    static unsigned char suffix[ MC_SIZE ];
    static unsigned short prefix[ MC_SIZE ];

    if ( code == LZW_INIT )
    {
        lbuf = lhead = fl_realloc( lhead, im->w + 1 + 4096 );

        bpp = CodeSize;
        ClearCode = 1 << bpp;
        EOFCode = ClearCode + 1;
        CodeSize = bpp + 1;

        for ( incode = ClearCode; --incode >= 0; )
        {
            *( suffix + incode ) = incode;
            *( prefix + incode ) = 0;
        }

        avail = ClearCode + 2;
        oldcode = -1;
        stackp = stack;
        return lbuf ? 0 : -1;
    }

    if ( code == ClearCode )
    {
        CodeSize = bpp + 1;
        avail = ClearCode + 2;
        oldcode = -1;
        return 0;
    }


    if ( code > avail || code < 0 )
    {
        flimage_error( im, "GIFLZW(%s): Bad code 0x%04x", im->infile, code );
        return -1;
    }

    if ( oldcode == -1 )
    {
        OUTPIX( suffix[ code ] );
        firstchar = oldcode = code;


        flush_buffer( im );
        return 0;
    }

    incode = code;
    if ( code == avail )
    {
        *stackp++ = firstchar;
        code = oldcode;
    }

    while ( code > ClearCode )
    {
        *stackp++ = suffix[ code ];
        code = prefix[ code ];
    }

    if ( avail >= 4096 )
    {
        flimage_error( im, "GIFLZW(%s): BadBlock--TableFull", im->infile );
        return -1;
    }

    *stackp++ = firstchar = suffix[ code ];
    prefix[ avail ] = oldcode;
    suffix[ avail ] = firstchar;

    avail++;
    if ( ( avail & gif_codemask[ CodeSize ] ) == 0 && avail < 4096 )
        CodeSize++;

    oldcode = incode;

    do
    {
        OUTPIX( *--stackp );
    }
    while ( stackp > stack );


    flush_buffer( im );

    return 0;
}
