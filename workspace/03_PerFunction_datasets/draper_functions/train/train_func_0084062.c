paintExpose(int ex, int ey, int ew, int eh) {
    Graphics &g = getGraphics();
    XRectangle r;

    r.x = ex;
    r.y = ey;
    r.width = ew;
    r.height = eh;

    g.setClipRectangles(&r, 1);

    const int ee = 0;

    if (ex < ee) {
        ew += ex;
        ex = 0;
    } else {
        ex -= ee;
        ew += ee;
    }
    if (ey < ee) {
        eh += ey;
        ey = 0;
    } else {
        ey -= ee;
        eh += ee;
    }
    if (ex + ew < width()) {
        ew += ee;
    } else {
        ew = width() - ex;
    }
    if (ey + eh + ee < height()) {
        eh += ee;
    } else {
        eh = height() - ey;
    }

    YRect r1(ex, ey, ew, eh);
    if (r1.width() > 0 && r1.height() > 0) {
        if (fDoubleBuffer) {
            ref<YPixmap> pixmap = beginPaint(r1);
            Graphics g1(pixmap, ex, ey);

            paint(g1, r1);
            endPaint(g, pixmap, r1);
        } else {
            paint(g, r1);
        }
    }
    g.resetClip();


}
