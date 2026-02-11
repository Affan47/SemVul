gui_create_main_win(void)
{
    GtkWidget* win;
    GtkWidget* vbox;
    GtkWidget* item;

    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    MainWin = win;
    gtk_window_set_title(GTK_WINDOW(win), "Graphical Disk Map "VERSION);
    gtk_window_set_role(GTK_WINDOW(win), "Main window");
    gtk_window_set_default_icon(create_pixbuf("gdmap_icon.png"));
    gtk_window_set_default_size(GTK_WINDOW(win), 700, 450);
    g_object_add_weak_pointer(G_OBJECT(win), (void*)&MainWin);


    vbox = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(vbox);
    gtk_container_add(GTK_CONTAINER(win), vbox);


    gui_setup_actions(win);

    if ((item = gtk_ui_manager_get_widget(UIManager, "/ui/MainMenu")) != NULL)
        gtk_box_pack_start(GTK_BOX (vbox), item, FALSE, FALSE, 0);

    if ((item = gtk_ui_manager_get_widget(UIManager, "/ui/ToolBar")) != NULL)
        gtk_box_pack_start(GTK_BOX (vbox), item, FALSE, FALSE, 0);

    if ((item = gui_create_path_box()) != NULL)
        gtk_box_pack_start(GTK_BOX (vbox), item, FALSE, FALSE, 0);

    if ((item = gui_create_display_box()) != NULL)
        gtk_box_pack_start(GTK_BOX (vbox), item, TRUE, TRUE, 0);

    if ((item = gui_create_status_bar()) != NULL)
        gtk_box_pack_start(GTK_BOX (vbox), item, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT (win), "delete_event",
                     G_CALLBACK(on_main_win_delete_event), NULL);

    gui_buttons_update();

    gtk_widget_show(win);

    pref_set_redraw_callback(gui_tree_redraw);

    return win;
}
