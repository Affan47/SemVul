redraw_frame(client_t *c)
{
    int x, y;

    if (c && c->decor) {
        XClearWindow(dpy, c->frame);
        if (!c->shaded) XDrawLine(dpy, c->frame, border_gc,
            0, frame_height(c) - BW(c) + BW(c)/2,
            c->geom.w, frame_height(c) - BW(c) + BW(c)/2);
        XDrawLine(dpy, c->frame, border_gc,
            c->geom.w - frame_height(c) + BW(c)/2, 0,
            c->geom.w - frame_height(c) + BW(c)/2, frame_height(c));

        if (!c->trans && c->name) {
            x = opt_pad + DESCENT/2;
            y = opt_pad + ASCENT;
#ifdef XFT
#ifdef X_HAVE_UTF8_STRING
            XftDrawStringUtf8(c->xftdraw, &xft_fg, xftfont, x, y,
                (unsigned char *)c->name, strlen(c->name));
#else
            XftDrawString8(c->xftdraw, &xft_fg, xftfont, x, y,
                (unsigned char *)c->name, strlen(c->name));
#endif
#else
#ifdef X_HAVE_UTF8_STRING
            Xutf8DrawString(dpy, c->frame, font_set, string_gc, x, y,
                c->name, strlen(c->name));
#else
            XDrawString(dpy, c->frame, string_gc, x, y,
                c->name, strlen(c->name));
#endif
#endif
        }
    }
}
