draw (Canvas* c, Graphic* gs) {
    PSBrush* br = gs->GetBrush();

    if (!br->None()) {
        Coord x0 = _x0, y0 = _y0, x1 = _x1, y1 = _y1;

        if (Head()) _head->CorrectedTip(x0, y0, br, gs->GetTransformer());
        if (Tail()) _tail->CorrectedTip(x1, y1, br, gs->GetTransformer());

        update(gs);
#if __GNUC__>=2 && __GNUC_MINOR__>=5 || __GNUC__>=3
#undef Line
        _p->Line(c, x0, y0, x1, y1);
#define Line _lib_iv(Line)
#else
        _p->Line(c, x0, y0, x1, y1);
#endif
    }

    if (Head()) ArrowheadDraw(_head, c, gs);
    if (Tail()) ArrowheadDraw(_tail, c, gs);
}
