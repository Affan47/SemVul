canvas_dosetbounds(t_canvas *x, int x1, int y1, int x2, int y2)
{
    int heightwas = y2 - y1;
    int heightchange = y2 - y1 - (x->gl_screeny2 - x->gl_screeny1);
    if (x->gl_screenx1 == x1 && x->gl_screeny1 == y1 &&
        x->gl_screenx2 == x2 && x->gl_screeny2 == y2)
            return;
    x->gl_screenx1 = x1;
    x->gl_screeny1 = y1;
    x->gl_screenx2 = x2;
    x->gl_screeny2 = y2;
    if (!glist_isgraph(x) && (x->gl_y2 < x->gl_y1))
    {


        t_float diff = x->gl_y1 - x->gl_y2;
        t_gobj *y;
        x->gl_y1 = heightwas * diff;
        x->gl_y2 = x->gl_y1 - diff;


        for (y = x->gl_list; y; y = y->g_next)
            if (pd_checkobject(&y->g_pd))
                gobj_displace(y, x, 0, heightchange);
        canvas_redraw(x);
    }
}
