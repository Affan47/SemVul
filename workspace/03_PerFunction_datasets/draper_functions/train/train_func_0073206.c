oki_adpcm_init(oki_adpcm_state_t *s, int bit_rate)
{
    if (bit_rate != 32000  &&  bit_rate != 24000)
        return NULL;
    if (s == NULL)
    {
        if ((s = (oki_adpcm_state_t *) malloc(sizeof(*s))) == NULL)
            return  NULL;
    }
    memset(s, 0, sizeof(*s));
    s->bit_rate = bit_rate;

    return  s;
}
