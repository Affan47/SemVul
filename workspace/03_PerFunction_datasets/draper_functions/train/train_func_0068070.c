sigreceive_perf8(t_int *w)
{
    t_sigreceive *x = (t_sigreceive *)(w[1]);
    t_sample *out = (t_sample *)(w[2]);
    int n = (int)(w[3]);
    t_sample *in = x->x_wherefrom;
    if (in)
    {
        for (; n; n -= 8, in += 8, out += 8)
        {
            out[0] = in[0]; out[1] = in[1]; out[2] = in[2]; out[3] = in[3];
            out[4] = in[4]; out[5] = in[5]; out[6] = in[6]; out[7] = in[7];
        }
    }
    else
    {
        for (; n; n -= 8, in += 8, out += 8)
        {
            out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
            out[4] = 0; out[5] = 0; out[6] = 0; out[7] = 0;
        }
    }
    return (w+4);
}
