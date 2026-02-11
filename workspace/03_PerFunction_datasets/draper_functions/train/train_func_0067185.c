modula(int x, int y) {

    const int s = 16;

    char data[32];
    long pattern = 0;

    register int i;

    FbRootWindow root(screen);

    for (i = 0; i < s; i++) {
        pattern <<= 1;
        if ((i % x) == 0)
            pattern |= 0x0001;
    }

    for (i = 0; i < s; i++) {
        if ((i %  y) == 0) {
            data[(i * 2)] = (char) 0xff;
            data[(i * 2) + 1] = (char) 0xff;
        } else {
            data[(i * 2)] = pattern & 0xff;
            data[(i * 2) + 1] = (pattern >> 8) & 0xff;
        }
    }


    Pixmap bitmap, r_bitmap;


    bitmap = XCreateBitmapFromData(display(),
                                   root.window(), data, s, s);


    r_bitmap = XCreatePixmap(display(),
                             root.window(), s, s,
                             (root.depth() == 32 ? 24 : root.depth()));

    FbTk::Color f(fore, screen), b(back, screen);

    if (! f.isAllocated())
        f.setPixel(WhitePixel(display(), screen));
    if (! b.isAllocated())
        b.setPixel(BlackPixel(display(), screen));

    FbTk::GContext gc(root);

    gc.setForeground(f);
    gc.setBackground(b);


    XCopyPlane(display(), bitmap, r_bitmap, gc.gc(),
               0, 0, s, s, 0, 0, 1l);

    gc.setTile(r_bitmap);
    gc.setFillStyle(FillTiled);

    pixmap = new Pixmap(XCreatePixmap(display(),
                                      root.window(),
                                      root.width(), root.height(),
                                      getRootDepth(root)));

    XFillRectangle(display(), *pixmap, gc.gc(), 0, 0,
                   root.width(), root.height());

    setRootAtoms(*pixmap, screen);
    root.setBackgroundPixmap(*pixmap);
    root.clear();

    XFreePixmap(display(), bitmap);
    XFreePixmap(display(), r_bitmap);
}
