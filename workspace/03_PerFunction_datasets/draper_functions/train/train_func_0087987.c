tabsend_dsp(t_tabsend *x, t_signal **sp)
{
    int i, vecsize;
    t_garray *a;

    if (!(a = (t_garray *)pd_findbyclass(x->x_arrayname, garray_class)))
    {
        if (*x->x_arrayname->s_name)
            pd_error(x, "tabsend~: %s: no such array", x->x_arrayname->s_name);
    }
    else if (!garray_getfloatwords(a, &vecsize, &x->x_vec))
        pd_error(x, "%s: bad template for tabsend~", x->x_arrayname->s_name);
    else
    {
        int n = sp[0]->s_n;
        int ticksper = sp[0]->s_sr/n;
        if (ticksper < 1) ticksper = 1;
        x->x_graphperiod = ticksper;
        if (x->x_graphcount > ticksper) x->x_graphcount = ticksper;
        if (n < vecsize) vecsize = n;
        garray_usedindsp(a);
        dsp_add(tabsend_perform, 3, x, sp[0]->s_vec, vecsize);
    }
}
