glist_getindex(t_glist *x, t_gobj *y)
{
    t_gobj *y2;
    int indx;

    for (y2 = x->gl_list, indx = 0; y2 && y2 != y; y2 = y2->g_next)
        indx++;
    return (indx);
}
