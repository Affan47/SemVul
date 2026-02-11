garray_resize_long(t_garray *x, long n)
{
    t_array *array = garray_getarray(x);
    t_glist *gl = x->x_glist;
    if (n < 1)
        n = 1;
    garray_fittograph(x, n, template_getfloat(
        template_findbyname(x->x_scalar->sc_template),
            gensym("style"), x->x_scalar->sc_vec, 1));
    array_resize_and_redraw(array, x->x_glist, n);
    if (x->x_usedindsp)
        canvas_update_dsp();
}
