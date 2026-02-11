mpc8_dec_base(GetBitContext *gb, int k, int n)
{
    int code = get_bits(gb, mpc8_cnk_len[k-1][n-1] - 1);

    if (code >= mpc8_cnk_lost[k-1][n-1])
        code = ((code << 1) | get_bits1(gb)) - mpc8_cnk_lost[k-1][n-1];

    return code;
}
