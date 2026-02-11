canvas_rename_method(t_canvas *x, t_symbol *s, int ac, t_atom *av)
{
    if (ac && av->a_type == A_SYMBOL)
        canvas_rename(x, av->a_w.w_symbol, 0);
    else if (ac && av->a_type == A_DOLLSYM)
    {
        t_canvasenvironment *e = canvas_getenv(x);
        canvas_setcurrent(x);
        canvas_rename(x, binbuf_realizedollsym(av->a_w.w_symbol,
            e->ce_argc, e->ce_argv, 1), 0);
        canvas_unsetcurrent(x);
    }
    else canvas_rename(x, gensym("Pd"), 0);
}
