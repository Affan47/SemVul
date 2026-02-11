drawclipped_gs (
    Canvas* c, Coord l, Coord b, Coord r, Coord t, Graphic31* gs
) {
    Graphic31 gstemp;

    GlyphIndex count = _body->count();
    for (GlyphIndex i = 0; i < count; i++) {
        Graphic31* gr = (Graphic31*) _body->component(i);
        concat_(gr, gr, gs, &gstemp);
        drawclipped_(gr, c, l, b, r, t, &gstemp);
    }
}
