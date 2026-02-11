text_eraseborder(t_text *x, t_glist *glist, char *tag)
{
    if (x->te_type == T_TEXT) return;
    sys_vgui(".x%lx.c delete %sR\n",
        glist_getcanvas(glist), tag);
    glist_eraseiofor(glist, x, tag);
}
