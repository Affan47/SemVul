tabwrite_tilde_redraw(t_tabwrite_tilde *x)
{
    t_garray *a = (t_garray *)pd_findbyclass(x->x_arrayname, garray_class);
    if (!a)
        bug("tabwrite_tilde_redraw");
    else garray_redraw(a);
}
