taskbar_constructor(plugin_instance *p)
{
    taskbar_priv *tb;
    GtkRequisition req;
    xconf *xc = p->xc;

    ENTER;
    tb = (taskbar_priv *) p;
    gtk_rc_parse_string(taskbar_rc);
    get_button_spacing(&req, GTK_CONTAINER(p->pwid), "");
    net_active_detect();

    tb->topxwin           = p->panel->topxwin;
    tb->tooltips          = 1;
    tb->icons_only        = 0;
    tb->accept_skip_pager = 1;
    tb->show_iconified    = 1;
    tb->show_mapped       = 1;
    tb->show_all_desks    = 0;
    tb->task_width_max    = TASK_WIDTH_MAX;
    tb->task_height_max   = p->panel->max_elem_height;
    tb->task_list         = g_hash_table_new(g_int_hash, g_int_equal);
    tb->focused_state     = GTK_STATE_ACTIVE;
    tb->normal_state      = GTK_STATE_NORMAL;
    tb->spacing           = 1;
    tb->use_mouse_wheel   = 1;
    tb->use_urgency_hint  = 1;

    XCG(xc, "tooltips", &tb->tooltips, enum, bool_enum);
    XCG(xc, "iconsonly", &tb->icons_only, enum, bool_enum);
    XCG(xc, "acceptskippager", &tb->accept_skip_pager, enum, bool_enum);
    XCG(xc, "showiconified", &tb->show_iconified, enum, bool_enum);
    XCG(xc, "showalldesks", &tb->show_all_desks, enum, bool_enum);
    XCG(xc, "showmapped", &tb->show_mapped, enum, bool_enum);
    XCG(xc, "usemousewheel", &tb->use_mouse_wheel, enum, bool_enum);
    XCG(xc, "useurgencyhint", &tb->use_urgency_hint, enum, bool_enum);
    XCG(xc, "maxtaskwidth", &tb->task_width_max, int);


    if (tb->task_height_max > TASK_HEIGHT_MAX)
        tb->task_height_max = TASK_HEIGHT_MAX;
    if (p->panel->orientation == GTK_ORIENTATION_HORIZONTAL) {
        tb->iconsize = MIN(p->panel->ah, tb->task_height_max) - req.height;
        if (tb->icons_only)
            tb->task_width_max = tb->iconsize + req.width;
    } else {
        if (p->panel->aw <= 30)
            tb->icons_only = 1;
        tb->iconsize = MIN(p->panel->aw, tb->task_height_max) - req.height;
        if (tb->icons_only)
            tb->task_width_max = tb->iconsize + req.height;
    }
    taskbar_build_gui(p);
    tb_net_client_list(NULL, tb);
    tb_display(tb);
    tb_net_active_window(NULL, tb);
    RET(1);
}
