glist_selectionindex(t_glist *x, t_gobj *y, int selected)
{
    t_gobj *y2;
    int indx;

    for (y2 = x->gl_list, indx = 0; y2 && y2 != y; y2 = y2->g_next)
        if (selected == glist_isselected(x, y2))
            indx++;
    return (indx);
}
