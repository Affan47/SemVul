bitstream_put(bitstream_state_t *s, uint8_t **c, uint32_t value, int bits)
{
    value &= ((1 << bits) - 1);
    if (s->lsb_first)
    {
        if (s->residue + bits <= 32)
        {
            s->bitstream |= (value << s->residue);
            s->residue += bits;
        }
        while (s->residue >= 8)
        {
            s->residue -= 8;
            *(*c)++ = (uint8_t) (s->bitstream & 0xFF);
            s->bitstream >>= 8;
        }
    }
    else
    {
        if (s->residue + bits <= 32)
        {
            s->bitstream = (s->bitstream << bits) | value;
            s->residue += bits;
        }
        while (s->residue >= 8)
        {
            s->residue -= 8;
            *(*c)++ = (uint8_t) ((s->bitstream >> s->residue) & 0xFF);
        }
    }
}
