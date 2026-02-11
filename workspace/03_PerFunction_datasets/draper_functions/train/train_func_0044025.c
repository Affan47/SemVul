fl_get_rgb_pixel( FL_COLOR packed,
                  int *    newpix )
{
    FL_STATE *s = &fl_state[ fl_vmode ];
    unsigned long pixel;
    int max_col;
    static Colormap lastcolormap;
    static XColor *xcolor;
    static int new_col;
    XColor xc;

    unsigned int r = FL_GETR( packed );
    unsigned int g = FL_GETG( packed );
    unsigned int b = FL_GETB( packed );

    *newpix = 0;
    if ( s->vclass == TrueColor || s->vclass == DirectColor )
        return rgb2pixel( r, g, b );
    else
    {
        xc.flags = DoRed | DoGreen | DoBlue;
        xc.red   = ( r << 8 ) | 0xff;
        xc.green = ( g << 8 ) | 0xff;
        xc.blue  = ( b << 8 ) | 0xff;

        new_col++;

        if ( ( *newpix = XAllocColor( flx->display, s->colormap, &xc ) ) )
            return xc.pixel;


        if ( ( max_col = FL_min( 256, 1 << s->depth ) ) == 0 )
            max_col = 256;

        if ( ! xcolor )
            xcolor = fl_malloc( 256 * sizeof *xcolor );


        if ( lastcolormap != s->colormap || new_col > 3 )
        {
            int i;

            for ( i = 0; i < max_col; i++ )
                xcolor[ i ].pixel = i;
            XQueryColors( flx->display, s->colormap, xcolor, max_col );
            lastcolormap = s->colormap;
            new_col = 0;
        }

        fli_find_closest_color( r, g, b, xcolor, max_col, &pixel );
        return pixel;
    }
}
