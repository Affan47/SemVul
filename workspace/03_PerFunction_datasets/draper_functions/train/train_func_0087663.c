get_new(t_symbol *why, int argc, t_atom *argv)
{
    t_get *x = (t_get *)pd_new(get_class);
    int i;
    t_getvariable *sp;
    x->x_templatesym = canvas_makebindsym(atom_getsymbolarg(0, argc, argv));
    if (argc) argc--, argv++;
    x->x_variables
        = (t_getvariable *)getbytes(argc * sizeof (*x->x_variables));
    x->x_nout = argc;
    for (i = 0, sp = x->x_variables; i < argc; i++, sp++)
    {
        sp->gv_sym = atom_getsymbolarg(i, argc, argv);
        sp->gv_outlet = outlet_new(&x->x_obj, 0);


    }
    return (x);
}
