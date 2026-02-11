sigdelread_float(t_sigdelread *x, t_float f)
{
    int samps;
    t_sigdelwrite *delwriter =
        (t_sigdelwrite *)pd_findbyclass(x->x_sym, sigdelwrite_class);
    x->x_deltime = f;
    if (delwriter)
    {
        int delsize = delwriter->x_cspace.c_n;
        x->x_delsamps = (int)(0.5 + x->x_sr * x->x_deltime)
            + x->x_n - x->x_zerodel;
        if (x->x_delsamps < x->x_n) x->x_delsamps = x->x_n;
        else if (x->x_delsamps > delwriter->x_cspace.c_n - DEFDELVS)
            x->x_delsamps = delwriter->x_cspace.c_n - DEFDELVS;
    }
}
