sigreceive_dsp(t_sigreceive *x, t_signal **sp)
{
    if (sp[0]->s_n != x->x_n)
    {
        pd_error(x, "receive~ %s: vector size mismatch", x->x_sym->s_name);
    }
    else
    {
        sigreceive_set(x, x->x_sym);
        if (sp[0]->s_n&7)
            dsp_add(sigreceive_perform, 3,
                x, sp[0]->s_vec, sp[0]->s_n);
        else dsp_add(sigreceive_perf8, 3,
            x, sp[0]->s_vec, sp[0]->s_n);
    }
}
