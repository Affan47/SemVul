gatom_retext(t_gatom *x, int senditup)
{
    binbuf_clear(x->a_text.te_binbuf);
    binbuf_add(x->a_text.te_binbuf, 1, &x->a_atom);
    if (senditup && glist_isvisible(x->a_glist))
        sys_queuegui(x, x->a_glist, gatom_redraw);
}
