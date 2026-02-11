sigdelread_dsp(t_sigdelread *x, t_signal **sp)
{
    t_sigdelwrite *delwriter =
        (t_sigdelwrite *)pd_findbyclass(x->x_sym, sigdelwrite_class);
    x->x_sr = sp[0]->s_sr * 0.001;
    x->x_n = sp[0]->s_n;
    if (delwriter)
    {
        sigdelwrite_updatesr(delwriter, sp[0]->s_sr);
        sigdelwrite_checkvecsize(delwriter, sp[0]->s_n);
        x->x_zerodel = (delwriter->x_sortno == ugen_getsortno() ?
            0 : delwriter->x_vecsize);
        sigdelread_float(x, x->x_deltime);
        dsp_add(sigdelread_perform, 4,
            sp[0]->s_vec, &delwriter->x_cspace, &x->x_delsamps, sp[0]->s_n);
    }
    else if (*x->x_sym->s_name)
        error("delread~: %s: no such delwrite~",x->x_sym->s_name);
}
