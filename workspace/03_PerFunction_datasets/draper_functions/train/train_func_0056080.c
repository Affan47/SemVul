canvas_fixlinesfor(t_canvas *x, t_text *text)
{
    t_linetraverser t;
    t_outconnect *oc;

    linetraverser_start(&t, x);
    while (oc = linetraverser_next(&t))
    {
        if (t.tr_ob == text || t.tr_ob2 == text)
        {
            sys_vgui(".x%lx.c coords l%lx %d %d %d %d\n",
                glist_getcanvas(x), oc,
                    t.tr_lx1, t.tr_ly1, t.tr_lx2, t.tr_ly2);
        }
    }
}
