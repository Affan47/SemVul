descramble(v22bis_state_t *s, int bit)
{
    int out_bit;

    bit &= 1;


    out_bit = (bit ^ (s->rx.scramble_reg >> 13) ^ (s->rx.scramble_reg >> 16)) & 1;
    s->rx.scramble_reg = (s->rx.scramble_reg << 1) | bit;

    if (s->rx.scrambler_pattern_count >= 64)
    {
        out_bit ^= 1;
        s->rx.scrambler_pattern_count = 0;
    }
    if (bit)
        s->rx.scrambler_pattern_count++;
    else
        s->rx.scrambler_pattern_count = 0;
    return out_bit;
}
