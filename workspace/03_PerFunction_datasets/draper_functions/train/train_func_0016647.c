drawGlyphs(Graphics & graphics, int x, int y,
                          char const * str, int len) {
    string_t xtext(str, len);
    if (0 == xtext.length()) return;

    int const y0(y - ascent());
    int const gcFn(graphics.function());

    char_t * xstr((char_t *) xtext.data());
    size_t xlen(xtext.length());

    TextPart *parts = partitions(xstr, xlen);


    switch (gcFn) {
        case GXxor:

            break;

        case GXcopy:


            break;
    }


    int xpos(0);
    for (TextPart *p = parts; p && p->length; ++p) {
        if (p->font) {
            XftGraphics::drawString(graphics, p->font,
                                    xpos + x, ascent() + y0,
                                    xstr, p->length);
        }

        xstr += p->length;
        xpos += p->width;
    }

    delete[] parts;


}
