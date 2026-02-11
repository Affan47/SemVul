bv_scan_next_unset_from(BitVector * bv, register const int from)
{
    register const f_u32 *const bits = bv->bits;
    register const int word_size = (bv->size >> 5) + 1;
    register int word_pos = from >> 5;
    register int bit_pos = (from & 31);
    register f_u32 word = ~(~(bits[word_pos]) >> bit_pos);

    if (from >= bv->size) {
        return -1;
    }
    if (word == 0xFFFFFFFF) {
        bit_pos = 0;
        do {
            word_pos++;
            if (word_pos >= word_size) {
                return -1;
            }
        } while (bits[word_pos] == 0xFFFFFFFF);
        word = bits[word_pos];
    }

    bit_pos += bv_get_1_offset(~word);

    return bv->curr_bit = ((word_pos << 5) + bit_pos);
}
