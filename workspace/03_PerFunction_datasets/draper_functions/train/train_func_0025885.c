make_vcut(int32 a, int32 l, int32 w, int32 h,
                      byte **pixels, byte *sig, int32 k,
                      int32 s_row(byte *, int32, int32),
                      int32 s_col(byte **, int32, int32, int32),
                      int32 size)
{
    int32 cut = 0;
    int32 left_weight = 0;

    if (k >= size) return;

    if (a)
    {
        int32 last_col_weight = 0;

        assert(w && h);

        while ((left_weight << 1) < a)
        {
            last_col_weight = s_col(pixels, l + cut, 0, h-1);
            left_weight += last_col_weight;
            cut++;
        }
        cut--;
        left_weight -= last_col_weight;
        sig[k] = (byte) ((256 *
                    (cut * h + h * ((a >> 1) - left_weight) / last_col_weight))
                 / (w * h));
        if (a - (left_weight << 1) > last_col_weight)
        {
            cut++; left_weight += last_col_weight;
        }
    }
    else
    {
        cut = w / 2;
        sig[k] = 128;
    }

    make_hcut(left_weight, l, cut, h, pixels, sig, k << 1, s_row, s_col, size);
    make_hcut(a - left_weight, l + cut, w - cut, h, pixels, sig, (k << 1) | 1, s_row, s_col, size);
}
