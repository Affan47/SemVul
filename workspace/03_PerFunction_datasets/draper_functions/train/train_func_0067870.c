alist_list(t_alist *x, t_symbol *s, int argc, t_atom *argv)
{
    int i;
    alist_clear(x);
    if (!(x->l_vec = (t_listelem *)getbytes(argc * sizeof(*x->l_vec))))
    {
        x->l_n = 0;
        error("list_alloc: out of memory");
        return;
    }
    x->l_n = argc;
    x->l_npointer = 0;
    for (i = 0; i < argc; i++)
    {
        x->l_vec[i].l_a = argv[i];
        if (x->l_vec[i].l_a.a_type == A_POINTER)
        {
            x->l_npointer++;
            gpointer_copy(x->l_vec[i].l_a.a_w.w_gpointer, &x->l_vec[i].l_p);
            x->l_vec[i].l_a.a_w.w_gpointer = &x->l_vec[i].l_p;
        }
    }
}
