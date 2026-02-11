vinlet_dsp(t_vinlet *x, t_signal **sp)
{
    t_signal *outsig;

    if (!x->x_buf)
        return;
    outsig = sp[0];
    if (x->x_directsignal)
    {
        signal_setborrowed(sp[0], x->x_directsignal);
    }
    else
    {
        dsp_add(vinlet_perform, 3, x, outsig->s_vec, outsig->s_vecsize);
        x->x_read = x->x_buf;
    }
}
