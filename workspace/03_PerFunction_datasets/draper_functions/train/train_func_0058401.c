flush () {
    GlyphIndex count = count_();

    for (GlyphIndex i = 0; i < count; i++) {
        Graphic31* gr = component_(i);
        concat_(gr, gr, this, gr);
        gr->flush();
    }
    Graphic31 n;
    *((Graphic31*) this) = *(&n);
}
