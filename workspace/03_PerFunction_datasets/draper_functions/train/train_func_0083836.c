UpdatePerspective () {
    register Perspective* p = perspective;
    Coord left, bottom, right, top;

    if (_graphic != nil) {
        GetGraphicBox(left, bottom, right, top);
        if (_x0 != left) {
            p->curx += _x0 - left;
            _x0 = left;
        }
        if (_y0 != bottom) {
            p->cury += _y0 - bottom;
            _y0 = bottom;
        }
        p->width = right - left + 2*_pad;
        p->height = top - bottom + 2*_pad;
    }
    p->Update();
}
