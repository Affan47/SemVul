create_bitmap_cursor( const char * source,
                      const char * mask,
                      int          w,
                      int          h,
                      int          hotx,
                      int          hoty )
{
    Pixmap s,
           m = None;
    XColor fg,
           bg;
    Cursor cur;
    Window win = fl_root;

    s = XCreateBitmapFromData( flx->display, win, source, w, h );

    if ( mask )
        m = XCreateBitmapFromData( flx->display, win, mask, w, h );

    fg.red = fg.green = fg.blue = 0;
    bg.red = bg.green = bg.blue = 0xffff;
    cur = XCreatePixmapCursor( flx->display, s, m, &fg, &bg, hotx, hoty );

    return cur;
}
