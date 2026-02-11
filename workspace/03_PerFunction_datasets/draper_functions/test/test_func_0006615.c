drawRotText(Drawable w, int screen, GC gc, const char *text, size_t len, int x, int y) const {

    Display *dpy = App::instance()->display();
    static GC my_gc = 0;
    int xp, yp, dir, ichar;

    if (text == NULL || len<1)
        return;

    dir = m_rotfont->dir;
    if (my_gc == 0)
        my_gc = XCreateGC(dpy, w, 0, 0);

    XCopyGC(dpy, gc, GCForeground|GCBackground, my_gc);


    XSetFillStyle(dpy, my_gc, FillStippled);


    for (size_t i = 0; i<len; i++) {
        ichar = text[i]-32;


        if (ichar >= 0 && ichar<95) {

            if (dir == 1) {
                xp = x-m_rotfont->per_char[ichar].ascent;
                yp = y-m_rotfont->per_char[ichar].rbearing;
            } else if (dir == 2) {
                xp = x-m_rotfont->per_char[ichar].rbearing;
                yp = y-m_rotfont->per_char[ichar].descent+1;
            } else {
                xp = x-m_rotfont->per_char[ichar].descent+1;
                yp = y+m_rotfont->per_char[ichar].lbearing;
            }


            XSetStipple(dpy, my_gc, m_rotfont->per_char[ichar].glyph.bm);

            XSetTSOrigin(dpy, my_gc, xp, yp);

            XFillRectangle(dpy, w, my_gc, xp, yp,
                           m_rotfont->per_char[ichar].glyph.bit_w,
                           m_rotfont->per_char[ichar].glyph.bit_h);


            if (dir == 1)
                y -= m_rotfont->per_char[ichar].width;
            else if (dir == 2)
                x -= m_rotfont->per_char[ichar].width;
            else
                y += m_rotfont->per_char[ichar].width;
        }
    }
}
