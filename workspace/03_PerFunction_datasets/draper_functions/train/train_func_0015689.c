Huffmancode(lame_internal_flags * const gfc, const unsigned int tableindex,
            int start, int end, gr_info const *gi)
{
    struct huffcodetab const *const h = &ht[tableindex];
    unsigned int const linbits = h->xlen;
    int     i, bits = 0;

    assert(tableindex < 32u);
    if (!tableindex)
        return bits;

    for (i = start; i < end; i += 2) {
        int16_t  cbits = 0;
        uint16_t xbits = 0;
        unsigned int xlen = h->xlen;
        unsigned int ext = 0;
        unsigned int x1 = gi->l3_enc[i];
        unsigned int x2 = gi->l3_enc[i + 1];

        assert(gi->l3_enc[i] >= 0);
        assert(gi->l3_enc[i+1] >= 0);

        if (x1 != 0u) {
            if (gi->xr[i] < 0.0f)
                ext++;
            cbits--;
        }

        if (tableindex > 15u) {

            if (x1 >= 15u) {
                uint16_t const linbits_x1 = x1 - 15u;
                assert(linbits_x1 <= h->linmax);
                ext |= linbits_x1 << 1u;
                xbits = linbits;
                x1 = 15u;
            }

            if (x2 >= 15u) {
                uint16_t const linbits_x2 = x2 - 15u;
                assert(linbits_x2 <= h->linmax);
                ext <<= linbits;
                ext |= linbits_x2;
                xbits += linbits;
                x2 = 15u;
            }
            xlen = 16;
        }

        if (x2 != 0u) {
            ext <<= 1;
            if (gi->xr[i + 1] < 0.0f)
                ext++;
            cbits--;
        }

        assert((x1 | x2) < 16u);

        x1 = x1 * xlen + x2;
        xbits -= cbits;
        cbits += h->hlen[x1];

        assert(cbits <= MAX_LENGTH);
        assert(xbits <= MAX_LENGTH);

        putbits2(gfc, h->table[x1], cbits);
        putbits2(gfc, (int)ext, xbits);
        bits += cbits + xbits;
    }
    return bits;
}
