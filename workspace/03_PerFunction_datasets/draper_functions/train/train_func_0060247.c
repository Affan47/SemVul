mud_connection_view_popup(MudConnectionView *view, GdkEventButton *event)
{
    GtkWidget *im_menu;
    GtkWidget *menu_item;
    GtkWidget *profile_menu;
    const GList *profiles;
    const GList *profile;
    GSList *group;

    if (view->priv->popup_menu)
        gtk_widget_destroy(view->priv->popup_menu);

    g_assert(view->priv->popup_menu == NULL);

    view->priv->popup_menu = gtk_menu_new();
    gtk_menu_attach_to_widget(GTK_MENU(view->priv->popup_menu),
            view->priv->terminal,
            popup_menu_detach);

    append_menuitem(view->priv->popup_menu,
            _("Close"),
            G_CALLBACK(mud_connection_view_close_current_cb),
            view);

    menu_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(view->priv->popup_menu), menu_item);

    append_stock_menuitem(view->priv->popup_menu,
            GTK_STOCK_COPY,
            NULL,
            view);
    append_stock_menuitem(view->priv->popup_menu,
            GTK_STOCK_PASTE,
            NULL,
            view);

    menu_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(view->priv->popup_menu), menu_item);

    profile_menu = gtk_menu_new();
    menu_item = gtk_menu_item_new_with_mnemonic(_("Change P_rofile"));
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), profile_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(view->priv->popup_menu), menu_item);

    group = NULL;
    profiles = mud_profile_get_profiles();
    profile = profiles;
    while (profile != NULL)
    {
        MudProfile *prof;

        prof = profile->data;


        g_object_ref(G_OBJECT(prof));

        menu_item = gtk_radio_menu_item_new_with_label(group,
                prof->name);
        group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(menu_item));
        gtk_menu_shell_append(GTK_MENU_SHELL(profile_menu), menu_item);

        if (prof == view->priv->profile)
            gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu_item), TRUE);

        g_signal_connect(G_OBJECT(menu_item),
                "toggled",
                G_CALLBACK(choose_profile_callback),
                view);
        g_object_set_data_full(G_OBJECT(menu_item),
                "profile",
                prof,
                (GDestroyNotify) g_object_unref);
        profile = profile->next;
    }

    menu_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(view->priv->popup_menu), menu_item);

    im_menu = gtk_menu_new();
    menu_item = gtk_menu_item_new_with_mnemonic(_("_Input Methods"));
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), im_menu);
    vte_terminal_im_append_menuitems(VTE_TERMINAL(view->priv->terminal),
            GTK_MENU_SHELL(im_menu));
    gtk_menu_shell_append(GTK_MENU_SHELL(view->priv->popup_menu), menu_item);

    gtk_widget_show_all(view->priv->popup_menu);
    gtk_menu_popup(GTK_MENU(view->priv->popup_menu),
            NULL, NULL,
            NULL, NULL,
            event ? event->button : 0,
            event ? event->time : gtk_get_current_event_time());
}
