draw (Canvas* c, Graphic* gs) {
    PSBrush* br = gs->GetBrush();

    if (!Head() && !Tail()) {
        SF_MultiLine::draw(c, gs);

    } else if (!br->None()) {
        int l = count()-1;
        Coord x0 = x()[0], y0 = y()[0], x1 = x()[l], y1 = y()[l];
        Coord tx0 = x0, ty0 = y0, tx1 = x1, ty1 = y1;

        if (Head()) _head->CorrectedTip(tx0, ty0, br, gs->GetTransformer());
        if (Tail()) _tail->CorrectedTip(tx1, ty1, br, gs->GetTransformer());

        x()[0] = tx0; y()[0] = ty0;
        x()[l] = tx1; y()[l] = ty1;

        update(gs);
#if __GNUC__>=2 && __GNUC_MINOR__>=5 || __GNUC__>=3
#undef MultiLine
        _p->MultiLine(c, x(), y(), count());
#define MultiLine _lib_iv(MultiLine)
#else
        _p->MultiLine(c, x(), y(), count());
#endif

        x()[0] = x0; y()[0] = y0;
        x()[l] = x1; y()[l] = y1;

        if (Head()) ArrowheadDraw(_head, c, gs);
        if (Tail()) ArrowheadDraw(_tail, c, gs);
    }
}
