at2_encode7bituncompressed(Octstr *source, int offset)
{
    int LSBmask[8] = { 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F };
    int MSBmask[8] = { 0x00, 0x40, 0x60, 0x70, 0x78, 0x7C, 0x7E, 0x7F };
    int destRemain = (int)ceil((octstr_len(source) * 7.0 + offset) / 8.0);
    int i = (offset?8-offset:7), iStore = offset;
    int posT, posS;
    Octstr *target = octstr_create("");
    int target_chr = 0, source_chr;


    for (posS = 0, posT = 0; (source_chr = octstr_get_char(source, posS++)) != -1;) {


        target_chr |= (source_chr & LSBmask[i]) << iStore;

        if (iStore != 0) {
            destRemain--;
            octstr_append_char(target, target_chr);
            target_chr = 0;
        }


        target_chr |= (source_chr & MSBmask[7 - i]) >> (8 - iStore) % 8;

        iStore = (--iStore < 0 ? 7 : iStore);

        if (iStore != 0)
            i = (++i > 7 ? 1 : i);
    }


    if (destRemain > 0)
        octstr_append_char(target, target_chr);

    return target;
}
