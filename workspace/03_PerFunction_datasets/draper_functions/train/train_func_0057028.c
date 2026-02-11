curve_getrect(t_gobj *z, t_glist *glist,
    t_word *data, t_template *template, t_float basex, t_float basey,
    int *xp1, int *yp1, int *xp2, int *yp2)
{
    t_curve *x = (t_curve *)z;
    int i, n = x->x_npoints;
    t_fielddesc *f = x->x_vec;
    int x1 = 0x7fffffff, x2 = -0x7fffffff, y1 = 0x7fffffff, y2 = -0x7fffffff;
    if (!fielddesc_getfloat(&x->x_vis, template, data, 0) ||
        (x->x_flags & NOMOUSE))
    {
        *xp1 = *yp1 = 0x7fffffff;
        *xp2 = *yp2 = -0x7fffffff;
        return;
    }
    for (i = 0, f = x->x_vec; i < n; i++, f += 2)
    {
        int xloc = glist_xtopixels(glist,
            basex + fielddesc_getcoord(f, template, data, 0));
        int yloc = glist_ytopixels(glist,
            basey + fielddesc_getcoord(f+1, template, data, 0));
        if (xloc < x1) x1 = xloc;
        if (xloc > x2) x2 = xloc;
        if (yloc < y1) y1 = yloc;
        if (yloc > y2) y2 = yloc;
    }
    *xp1 = x1;
    *yp1 = y1;
    *xp2 = x2;
    *yp2 = y2;
}
