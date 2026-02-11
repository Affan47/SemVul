gobj_shouldvis(t_gobj *x, struct _glist *glist)
{
    t_object *ob;
    if (!glist->gl_havewindow && glist->gl_isgraph && glist->gl_goprect &&
        glist->gl_owner && (pd_class(&x->g_pd) != scalar_class)
            && (pd_class(&x->g_pd) != garray_class))
    {


        int x1, y1, x2, y2, gx1, gy1, gx2, gy2, m;
        gobj_getrect(&glist->gl_gobj, glist->gl_owner, &x1, &y1, &x2, &y2);
        if (x1 > x2)
            m = x1, x1 = x2, x2 = m;
        if (y1 > y2)
            m = y1, y1 = y2, y2 = m;
        gobj_getrect(x, glist, &gx1, &gy1, &gx2, &gy2);
        if (gx1 < x1 || gx1 > x2 || gx2 < x1 || gx2 > x2 ||
            gy1 < y1 || gy1 > y2 || gy2 < y1 || gy2 > y2)
                return (0);
    }
    if (ob = pd_checkobject(&x->g_pd))
    {


        return (glist->gl_havewindow ||
            (ob->te_pd != canvas_class &&
                ob->te_pd->c_wb != &text_widgetbehavior) ||
            (ob->te_pd == canvas_class && (((t_glist *)ob)->gl_isgraph)) ||
            (glist->gl_goprect && (ob->te_type == T_TEXT)));
    }
    else return (1);
}
