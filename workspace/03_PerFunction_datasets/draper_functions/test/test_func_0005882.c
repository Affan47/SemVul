outlet_getsignalindex(t_outlet *x)
{
    int n = 0;
    t_outlet *o;
    for (o = x->o_owner->ob_outlet, n = 0; o && o != x; o = o->o_next)
        if (o->o_sym == &s_signal) n++;
    return (n);
}
