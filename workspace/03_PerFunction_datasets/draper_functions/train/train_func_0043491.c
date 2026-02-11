lpc10_random(lpc10_decode_state_t *s)
{
    int32_t ret_val;


    s->y[s->k] += s->y[s->j];
    ret_val = s->y[s->k];
    if (--s->k < 0)
        s->k = 4;
    if (--s->j < 0)
        s->j = 4;
    return ret_val;
}
