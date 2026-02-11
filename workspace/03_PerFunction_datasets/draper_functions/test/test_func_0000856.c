glob_verifyquit(void *dummy, t_floatarg f)
{
    t_glist *g, *g2;

    for (g = canvas_list; g; g = g->gl_next)
        if (g2 = glist_finddirty(g))
    {
        canvas_vis(g2, 1);
            sys_vgui("pdtk_canvas_menuclose .x%lx {.x%lx menuclose 3;\n}\n",
                     canvas_getrootfor(g2), g2);
        return;
    }
    if (f == 0 && sys_perf)
        sys_vgui("pdtk_check .pdwindow {really quit?} {pd quit} yes\n");
    else glob_quit(0);
}
