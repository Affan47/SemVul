canvas_drawlines(t_canvas *x)
{
    t_linetraverser t;
    t_outconnect *oc;
    {
        linetraverser_start(&t, x);
        while (oc = linetraverser_next(&t))
            sys_vgui(".x%lx.c create line %d %d %d %d -width %d -tags [list l%lx cord]\n",
                    glist_getcanvas(x),
                        t.tr_lx1, t.tr_ly1, t.tr_lx2, t.tr_ly2,
                            (outlet_getsymbol(t.tr_outlet) == &s_signal ? 2:1),
                                oc);
    }
}
