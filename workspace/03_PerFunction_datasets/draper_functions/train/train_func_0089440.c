fli_find_closest_color( int             r,
                        int             g,
                        int             b,
                        XColor        * map,
                        int             len,
                        unsigned long * pix )
{
    long mindiff = 0x7fffffffL,
         diff;
    int dr,
        dg,
        db;
    int i,
        k;

    for ( k = i = 0; i < len; i++ )
    {
        dr = r - ( ( map[ i ].red   >> 8 ) & 0xff );
        dg = g - ( ( map[ i ].green >> 8 ) & 0xff );
        db = b - ( ( map[ i ].blue  >> 8 ) & 0xff );


#if LINEAR_COLOR_DISTANCE
        diff = 3 * FL_abs( dr ) + 4 * FL_abs( dg ) + 2 * FL_abs( db );
#else
        diff = 3 * ( dr * dr ) + 4 * ( dg * dg ) + 2 * ( db * db );
#endif

        if ( diff < 0 )
            fprintf( stderr, "dr = %d dg = %d db = %d diff = %ld\n",
                     dr, dg, db, diff );

        if ( diff < mindiff )
        {
            mindiff = diff;
            k = i;
            *pix = map[ i ].pixel;
        }
    }

    return k;
}
