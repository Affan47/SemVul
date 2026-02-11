canvas_selectinrect(t_canvas *x, int lox, int loy, int hix, int hiy)
{
    t_gobj *y;
    for (y = x->gl_list; y; y = y->g_next)
    {
        int x1, y1, x2, y2;
        gobj_getrect(y, x, &x1, &y1, &x2, &y2);
        if (hix >= x1 && lox <= x2 && hiy >= y1 && loy <= y2
            && !glist_isselected(x, y))
                glist_select(x, y);
    }
}
