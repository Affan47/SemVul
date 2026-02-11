s_PDiffE_init(stream_state * st)
{
    stream_PDiff_state *const ss = (stream_PDiff_state *) st;
    int bits_per_row =
        ss->Colors * ss->BitsPerComponent * ss->Columns;
    static const byte cb_values[] = {
        0, cBits1, cBits2, 0, cBits4, 0, 0, 0, cBits8,
        0, 0, 0, 0, 0, 0, 0, cBits16
    };

    ss->row_count = (bits_per_row + 7) >> 3;
    ss->end_mask = (1 << (-bits_per_row & 7)) - 1;
    ss->case_index =
        cb_values[ss->BitsPerComponent] +
        (ss->Colors > 4 ? 0 : ss->Colors) + cEncode;
    return s_PDiff_reinit(st);
}
