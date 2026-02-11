fl_unset_clipping( void )
{
    if ( ! fli_perm_clip )
    {
        XSetClipMask( flx->display, flx->gc, None );
        cur_clip.x = cur_clip.y = cur_clip.width = cur_clip.height = 0;
    }
    else
    {
        XSetClipRectangles( flx->display, flx->gc, 0, 0, &fli_perm_xcr, 1,
                            Unsorted );
        cur_clip = fli_perm_xcr;
    }
}
