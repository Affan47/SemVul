canvas_vis(t_canvas *x, t_floatarg f)
{
    char buf[30];
    int flag = (f != 0);
    if (flag)
    {


        if (x->gl_editor && x->gl_havewindow)
        {
            sys_vgui("pdtk_canvas_raise .x%lx\n", x);
        }
        else
        {
            char cbuf[MAXPDSTRING];
            int cbuflen;
            t_canvas *c = x;
            canvas_create_editor(x);
            sys_vgui("pdtk_canvas_new .x%lx %d %d +%d+%d %d\n", x,
                (int)(x->gl_screenx2 - x->gl_screenx1),
                (int)(x->gl_screeny2 - x->gl_screeny1),
                (int)(x->gl_screenx1), (int)(x->gl_screeny1),
                x->gl_edit);
            snprintf(cbuf, MAXPDSTRING - 2, "pdtk_canvas_setparents .x%lx",
                (unsigned long)c);
            while (c->gl_owner) {
                c = c->gl_owner;
                cbuflen = strlen(cbuf);
                snprintf(cbuf + cbuflen,
                         MAXPDSTRING - cbuflen - 2,
                         " .x%lx", (unsigned long)c);
            }
            strcat(cbuf, "\n");
            sys_gui(cbuf);
            canvas_reflecttitle(x);
            x->gl_havewindow = 1;
            canvas_updatewindowlist();
        }
    }
    else
    {
        int i;
        t_canvas *x2;
        if (!x->gl_havewindow)
        {


            if (x->gl_editor)
                canvas_destroy_editor(x);
            return;
        }
        glist_noselect(x);
        if (glist_isvisible(x))
            canvas_map(x, 0);
        canvas_destroy_editor(x);
        sys_vgui("destroy .x%lx\n", x);
        for (i = 1, x2 = x; x2; x2 = x2->gl_next, i++)
            ;


        if (glist_isgraph(x) && x->gl_owner)
        {
            t_glist *gl2 = x->gl_owner;
            if (glist_isvisible(gl2))
                gobj_vis(&x->gl_gobj, gl2, 0);
            x->gl_havewindow = 0;
            if (glist_isvisible(gl2))
                gobj_vis(&x->gl_gobj, gl2, 1);
        }
        else x->gl_havewindow = 0;
        canvas_updatewindowlist();
    }
}
