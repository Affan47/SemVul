sigbiquad_perform(t_int *w)
{
    t_sample *in = (t_sample *)(w[1]);
    t_sample *out = (t_sample *)(w[2]);
    t_biquadctl *c = (t_biquadctl *)(w[3]);
    int n = (t_int)(w[4]);
    int i;
    t_sample last = c->c_x1;
    t_sample prev = c->c_x2;
    t_sample fb1 = c->c_fb1;
    t_sample fb2 = c->c_fb2;
    t_sample ff1 = c->c_ff1;
    t_sample ff2 = c->c_ff2;
    t_sample ff3 = c->c_ff3;
    for (i = 0; i < n; i++)
    {
        t_sample output =  *in++ + fb1 * last + fb2 * prev;
        if (PD_BIGORSMALL(output))
            output = 0;
        *out++ = ff1 * output + ff2 * last + ff3 * prev;
        prev = last;
        last = output;
    }
    c->c_x1 = last;
    c->c_x2 = prev;
    return (w+5);
}
