fl_color( FL_COLOR col )
{
    static int vmode = -1;
    long p;

    if ( flx->color != col || vmode != fl_vmode )
    {
        flx->color = col;
        vmode = fl_vmode;
        p = fl_get_pixel( col );
        XSetForeground( flx->display, flx->gc, p );
        fli_free_newpixel( p );
    }
}
