xpmtops_direct( const char * file,
                int          xo,
                int          yo,
                long         tran )
{
    short *pixels;
    fd2psCMAP *maps[ NMAPS ], *map;
    int set[ NMAPS ];
    int ncols, w, h, i, r, g, b;

    if ( ! ( pixels = read_xpm( file, &w, &h, &ncols, maps, set ) ) )
        return -1;

#ifdef DEBUG
    {
        int x, y;
        short *p;

        fprintf( stderr, "xmapfile: w=%d h=%d ncol=%d\n", w, h, ncols );

        for ( p = pixels, y = 0; y < h; y++ )
        {
            for ( x = 0; x < w; x++ )
                fprintf( stderr, "%1d", *p++ );
            fprintf(stderr, "\n" );
        }
    }
#endif


    if ( set[ CMAP ] + set[ GMAP ] + set[ G4MAP ] + set[ MMAP ] == 0 )
    {
        fprintf( stderr, "no usable colormap found\n" );
        return -1;
    }

    if ( set[ CMAP ] )
        map = maps[ CMAP ];
    else if ( set[ GMAP ])
        map = maps[ GMAP ];
    else if ( set[ G4MAP ] )
        map = maps[ G4MAP ];
    else
        map = maps[ MMAP ];


    if ( ! flps->colorps && set[ GMAP ] )
        map = maps[ GMAP ];


    fl_query_imap( tran, &r, &g, &b );
    for ( i = 0; i < ncols; i++ )
    {
        if ( map[ i ].red < 0 )
        {
            map[ i ].red   = r;
            map[ i ].green = g;
            map[ i ].blue  = b;
        }
    }


    ps_verbatim( "\n%% Start of pixmap file %s {\n", file );
    ps_output( "gsave\n" );
    ps_output( "%d %d translate\n", xo, yo );

    ( flps->colorps ? image2colorps : image2grayps )( pixels, w, h, map,
                                                      ncols, 0 );

    ps_verbatim( "\ngrestore %%}\n" );

    return 0;
}
