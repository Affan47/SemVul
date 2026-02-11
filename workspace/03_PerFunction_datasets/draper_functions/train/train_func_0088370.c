fl_drawmode( int request )
{
    if ( drmode != request )
        XSetFunction( flx->display, flx->gc, drmode = request );
}
