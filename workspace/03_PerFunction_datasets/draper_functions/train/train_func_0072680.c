updateclut (uaecptr clut, int start, int count)
{
    int i, changed = 0;
    clut += start * 3;
    for (i = start; i < start + count; i++) {
        int r = get_byte (clut);
        int g = get_byte (clut + 1);
        int b = get_byte (clut + 2);


        changed |= picasso96_state.CLUT[i].Red != r
            || picasso96_state.CLUT[i].Green != g
            || picasso96_state.CLUT[i].Blue != b;
        if (picasso96_state.CLUT[i].Pad) {
            changed = 1;
            picasso96_state.CLUT[i].Pad = 0;
        }
        picasso96_state.CLUT[i].Red = r;
        picasso96_state.CLUT[i].Green = g;
        picasso96_state.CLUT[i].Blue = b;
        clut += 3;
    }
    changed |= picasso_palette ();
    return changed;
}
