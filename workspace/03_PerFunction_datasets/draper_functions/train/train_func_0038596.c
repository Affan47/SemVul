draw (Canvas* c, Graphic* gs) {
    if (!gs->GetBrush()->None()) {
        update(gs);
        _p->Circle(c, _x, _y, PIN_RAD);
#if __GNUC__>=2 && __GNUC_MINOR__>=5 || __GNUC__>=3
#undef Line
        _p->Line(c, _x, _y - PIN_RAD, _x, _y + PIN_RAD);
        _p->Line(c, _x - PIN_RAD, _y, _x + PIN_RAD, _y);
#define Line _lib_iv(Line)
#else
        _p->Line(c, _x, _y - PIN_RAD, _x, _y + PIN_RAD);
        _p->Line(c, _x - PIN_RAD, _y, _x + PIN_RAD, _y);
#endif
    }
}
