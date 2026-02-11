createPixmap(Drawable d, Pixmap &pixmap, Pixmap &mask) const {

    Display *disp = FbTk::App::instance()->display();
    pixmap = XCreatePixmap(disp, d, width(), height(), m_bpp);

    XPutImage(disp, pixmap,
              DefaultGC(FbTk::App::instance()->display(), 0),
              const_cast<XImage *>(m_ximage),
              0, 0,
              0, 0,
              width(), height());

    mask = 0;

    if (!m_use_color_key)
        return;


    Surface one_bit(width(), height(), 1);
    for (int y=0; y<height(); y++) {
        for (int x=0; x<width(); x++) {
            if (XGetPixel(m_ximage, x, y) == m_color_key)
                XPutPixel(one_bit.m_ximage, x, y, 0);
            else
                XPutPixel(one_bit.m_ximage, x, y, 1);
        }
    }

    XGCValues values;
    values.foreground = 1;
    values.background = 0;
    mask = XCreatePixmap(disp, d, width(), height(), 1);
    GC gc = XCreateGC(disp, mask,
                      GCForeground | GCBackground, &values);


    XPutImage(disp, mask, gc, one_bit.m_ximage, 0, 0, 0, 0,
              width(), height());

    XFreeGC(disp, gc);

}

}
