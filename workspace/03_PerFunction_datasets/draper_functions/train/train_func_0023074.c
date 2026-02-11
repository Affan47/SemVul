max_new(t_symbol *s, int argc, t_atom *argv)
{
    if (argc > 1) post("max~: extra arguments ignored");
    if (argc)
    {
        t_scalarmax *x = (t_scalarmax *)pd_new(scalarmax_class);
        floatinlet_new(&x->x_obj, &x->x_g);
        x->x_g = atom_getfloatarg(0, argc, argv);
        outlet_new(&x->x_obj, &s_signal);
        x->x_f = 0;
        return (x);
    }
    else
    {
        t_max *x = (t_max *)pd_new(max_class);
        inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
        outlet_new(&x->x_obj, &s_signal);
        x->x_f = 0;
        return (x);
    }
}
