canvas_istable(t_canvas *x)
{
    t_atom *argv = (x->gl_obj.te_binbuf? binbuf_getvec(x->gl_obj.te_binbuf):0);
    int argc = (x->gl_obj.te_binbuf? binbuf_getnatom(x->gl_obj.te_binbuf) : 0);
    int istable = (argc && argv[0].a_type == A_SYMBOL &&
        argv[0].a_w.w_symbol == gensym("table"));
    return (istable);
}
