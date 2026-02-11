graph_ylabel(t_glist *x, t_symbol *s, int argc, t_atom *argv)
{
    int i;
    if (argc < 1) error("graph_ylabel: no x value given");
    else
    {
        x->gl_ylabelx = atom_getfloat(argv);
        argv++; argc--;
        x->gl_ylabel = (t_symbol **)t_resizebytes(x->gl_ylabel,
            x->gl_nylabels * sizeof (t_symbol *), argc * sizeof (t_symbol *));
        x->gl_nylabels = argc;
        for (i = 0; i < argc; i++) x->gl_ylabel[i] = atom_gensym(&argv[i]);
    }
    glist_redraw(x);
}
