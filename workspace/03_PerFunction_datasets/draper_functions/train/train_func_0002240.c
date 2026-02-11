powtodb_tilde_perform(t_int *w)
{
    t_sample *in = *(t_sample **)(w+1), *out = *(t_sample **)(w+2);
    t_int n = *(t_int *)(w+3);
    for (; n--; in++, out++)
    {
        t_sample f = *in;
        if (f <= 0) *out = 0;
        else
        {
            t_sample g = 100 + 10./LOGTEN * log(f);
            *out = (g < 0 ? 0 : g);
        }
    }
    return (w + 4);
}
