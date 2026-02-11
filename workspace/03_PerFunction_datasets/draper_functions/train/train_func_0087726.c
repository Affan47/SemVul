CI_GetRowzeroCharInfo_2D(const XFontStruct *fs, unsigned col, const XCharStruct *def, const XCharStruct*& cs)
{
    cs = def;
    if (fs->min_byte1 == 0 &&
        col >= fs->min_char_or_byte2 && col <= fs->max_char_or_byte2) {
        if (fs->per_char == NULL) {
            cs = &fs->min_bounds;
        } else {
            cs = &fs->per_char[(col - fs->min_char_or_byte2)];
            if (CI_NonExistChar(cs)) cs = def;
        }
    }
}
