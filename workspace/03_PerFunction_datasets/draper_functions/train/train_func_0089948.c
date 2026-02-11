drawRotText(Drawable w, int screen, GC gc, const char* text, size_t len, int x, int y, FbTk::Orientation orient) const {

    if (!text || !*text || len<1)
        return;

    Display *dpy = App::instance()->display();
    static GC my_gc = 0;
    int xp, yp, ichar;

    XRotFontStruct *rotfont = m_rotfonts[orient];

    if (my_gc == 0)
        my_gc = XCreateGC(dpy, w, 0, 0);

    XCopyGC(dpy, gc, GCForeground|GCBackground, my_gc);


    XSetFillStyle(dpy, my_gc, FillStippled);


    for (size_t i = 0; i<len; i++) {
        ichar = text[i]-32;


        if (ichar >= 0 && ichar<95) {

            if (orient == ROT270) {
                xp = x-rotfont->per_char[ichar].ascent;
                yp = y-rotfont->per_char[ichar].rbearing;
            } else if (orient == ROT180) {
                xp = x-rotfont->per_char[ichar].rbearing;
                yp = y-rotfont->per_char[ichar].descent+1;
            } else {
                xp = x-rotfont->per_char[ichar].descent;
                yp = y+rotfont->per_char[ichar].lbearing;
            }


            XSetStipple(dpy, my_gc, rotfont->per_char[ichar].glyph.bm);

            XSetTSOrigin(dpy, my_gc, xp, yp);

            XFillRectangle(dpy, w, my_gc, xp, yp,
                           rotfont->per_char[ichar].glyph.bit_w,
                           rotfont->per_char[ichar].glyph.bit_h);


            if (orient == ROT270)
                y -= rotfont->per_char[ichar].width;
            else if (orient == ROT180)
                x -= rotfont->per_char[ichar].width;
            else
                y += rotfont->per_char[ichar].width;
        }
    }
}
