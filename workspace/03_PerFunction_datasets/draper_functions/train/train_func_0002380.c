huff_decode(huff_tables *pH)
{
    int symbol;


    if ((symbol = pH->look_up[m_bit_buf >> 24]) < 0) {

        int ofs = 23;
        do {
            symbol = pH->tree[-(int)(symbol + ((m_bit_buf >> ofs) & 1))];
            ofs--;
        } while (symbol < 0);

        get_bits_no_markers(8 + (23 - ofs));
    } else
        get_bits_no_markers(pH->code_size[symbol]);

    return symbol;
}
