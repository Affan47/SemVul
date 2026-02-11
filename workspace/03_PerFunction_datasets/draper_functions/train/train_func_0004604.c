curve_to(
    Coord x, Coord y, Coord x1, Coord y1, Coord x2, Coord y2
) {
    CanvasRep* c = rep();
    PathRenderInfo* p = &CanvasRep::path_;
    Coord px = p->curx_;
    Coord py = p->cury_;

    if (straight(c->matrix(), px, py, x1, y1, x2, y2, x, y)) {
        line_to(x, y);
    } else {
        Coord xx = mid(x1, x2);
        Coord yy = mid(y1, y2);
        Coord x11 = mid(px, x1);
        Coord y11 = mid(py, y1);
        Coord x22 = mid(x2, x);
        Coord y22 = mid(y2, y);
        Coord x12 = mid(x11, xx);
        Coord y12 = mid(y11, yy);
        Coord x21 = mid(xx, x22);
        Coord y21 = mid(yy, y22);
        Coord cx = mid(x12, x21);
        Coord cy = mid(y12, y21);

        curve_to(cx, cy, x11, y11, x12, y12);
        curve_to(x, y, x21, y21, x22, y22);
    }
}
