g711_transcode(g711_state_t *s,
                   uint8_t g711_out[],
                   const uint8_t g711_in[],
                   int g711_bytes)
{
    int i;

    if (s->mode == G711_ALAW)
    {
        for (i = 0;  i < g711_bytes;  i++)
            g711_out[i] = alaw_to_ulaw_table[g711_in[i]];

    }
    else
    {
        for (i = 0;  i < g711_bytes;  i++)
            g711_out[i] = ulaw_to_alaw_table[g711_in[i]];

    }

    return g711_bytes;
}
