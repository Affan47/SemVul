lv_create (GNCLotViewer *lv)
{
    gchar *win_title;
    gint position;
    GtkBuilder *builder;
    GtkWidget *widget;

    builder = gtk_builder_new();
    gnc_builder_add_from_file (builder, "dialog-lot-viewer.glade", "Lot Viewer Window");

    lv->window = GTK_WIDGET(gtk_builder_get_object (builder, "Lot Viewer Window"));

    win_title = g_strdup_printf (_("Lots in Account %s"),
                                 xaccAccountGetName(lv->account));
    gtk_window_set_title (GTK_WINDOW (lv->window), win_title);
    g_free (win_title);

#ifdef LOTS_READY_FOR_SHOWTIME
    lv->regview_button = GTK_BUTTON(glade_xml_get_widget (builder, "regview button"));
#endif
    lv->delete_button = GTK_BUTTON(gtk_builder_get_object (builder, "delete button"));
    lv->scrub_lot_button = GTK_BUTTON(gtk_builder_get_object (builder, "scrub lot button"));
    lv->new_lot_button = GTK_BUTTON(gtk_builder_get_object (builder, "new lot button"));

    lv->lot_view = GTK_TREE_VIEW(gtk_builder_get_object (builder, "lot view"));
    lv->only_show_open_lots_checkbutton = GTK_TOGGLE_BUTTON(gtk_builder_get_object (builder, "only show open lots checkbutton"));
    lv_init_lot_view(lv);
    lv->lot_notes = GTK_TEXT_VIEW(gtk_builder_get_object (builder, "lot notes text"));
    lv->title_entry = GTK_ENTRY (gtk_builder_get_object (builder, "lot title entry"));

    lv->split_in_lot_view = GTK_TREE_VIEW(gtk_builder_get_object (builder, "split in lot view"));
    lv->split_free_view = GTK_TREE_VIEW(gtk_builder_get_object (builder, "split free view"));
    lv_init_split_views(lv);

    lv->add_split_to_lot_button = GTK_BUTTON(gtk_builder_get_object (builder, "add split to lot button"));
    lv->remove_split_from_lot_button = GTK_BUTTON(gtk_builder_get_object (builder, "remove split from lot button"));
    lv_init_split_buttons(lv);


    if (gnc_prefs_get_bool(GNC_PREFS_GROUP_GENERAL, GNC_PREF_SAVE_GEOMETRY))
    {
        GObject *object;
        object = gtk_builder_get_object (builder, "lot vpaned");
        gnc_prefs_bind (GNC_PREFS_GROUP, GNC_PREF_VPOS, object, "position");

        object = gtk_builder_get_object (builder, "lot hpaned");
        gnc_prefs_bind (GNC_PREFS_GROUP, GNC_PREF_HPOS, object, "position");
    }

    lv->selected_lot = NULL;


    gtk_builder_connect_signals(builder, lv);
    g_object_unref(G_OBJECT(builder));

    lv_update_split_buttons(lv);

    gnc_restore_window_size(GNC_PREFS_GROUP, GTK_WINDOW(lv->window));
}
