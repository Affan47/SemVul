canvas_displaceselection(t_canvas *x, int dx, int dy)
{
    t_selection *y;
    int resortin = 0, resortout = 0;
    if (!canvas_undo_already_set_move)
    {
        canvas_setundo(x, canvas_undo_move, canvas_undo_set_move(x, 1),
            "motion");
        canvas_undo_already_set_move = 1;
    }
    for (y = x->gl_editor->e_selection; y; y = y->sel_next)
    {
        t_class *cl = pd_class(&y->sel_what->g_pd);
        gobj_displace(y->sel_what, x, dx, dy);
        if (cl == vinlet_class) resortin = 1;
        else if (cl == voutlet_class) resortout = 1;
    }
    if (resortin) canvas_resortinlets(x);
    if (resortout) canvas_resortoutlets(x);
    sys_vgui("pdtk_canvas_getscroll .x%lx.c\n", x);
    if (x->gl_editor->e_selection)
        canvas_dirty(x, 1);
}
