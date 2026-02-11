init_login_window(void)
{
    GladeXML *xml_tree;
    GtkTextIter end;

    login_window = glade_xml_get_widget(dialog_xml, "login_window");

    if (!login_window) {
        error_dialog("Out of date dialog.glade", "Did you run 'make install'?");
        exit(1);
    }

    gtk_window_set_transient_for(
        GTK_WINDOW(login_window), GTK_WINDOW(window_root));

    xml_tree = glade_get_widget_tree(GTK_WIDGET(login_window));

    button_login =
        glade_xml_get_widget(dialog_xml,"button_login");
    button_create_account =
        glade_xml_get_widget(dialog_xml,"button_create_account");
    button_go_metaserver =
        glade_xml_get_widget(dialog_xml,"button_go_metaserver");
    button_exit_client =
        glade_xml_get_widget(dialog_xml,"button_exit_client");
    label_account_login_status =
        glade_xml_get_widget(dialog_xml,"label_account_login_status");
    login_pane[TEXTVIEW_MOTD].textview =
        glade_xml_get_widget(dialog_xml,"textview_motd");

    textbuf_motd =
        gtk_text_view_get_buffer(
            GTK_TEXT_VIEW(login_pane[TEXTVIEW_MOTD].textview));

    add_tags_to_textbuffer(&login_pane[TEXTVIEW_MOTD], textbuf_motd);
    add_style_to_textbuffer(&login_pane[TEXTVIEW_MOTD], NULL);
    gtk_text_buffer_get_end_iter(login_pane[TEXTVIEW_MOTD].textbuffer, &end);
    login_pane[TEXTVIEW_MOTD].textmark =
        gtk_text_buffer_create_mark(
            login_pane[TEXTVIEW_MOTD].textbuffer, NULL, &end, FALSE);

    login_pane[TEXTVIEW_NEWS].textview =
        glade_xml_get_widget(dialog_xml,"textview_news");

    textbuf_news =
        gtk_text_view_get_buffer(
            GTK_TEXT_VIEW(login_pane[TEXTVIEW_NEWS].textview));

    add_tags_to_textbuffer(&login_pane[TEXTVIEW_NEWS], textbuf_news);
    add_style_to_textbuffer(&login_pane[TEXTVIEW_NEWS], NULL);
    gtk_text_buffer_get_end_iter(login_pane[TEXTVIEW_NEWS].textbuffer, &end);
    login_pane[TEXTVIEW_NEWS].textmark =
        gtk_text_buffer_create_mark(
            login_pane[TEXTVIEW_NEWS].textbuffer, NULL, &end, FALSE);

    entry_account_name =
        glade_xml_get_widget(dialog_xml,"entry_account_name");
    entry_account_password =
        glade_xml_get_widget(dialog_xml,"entry_account_password");

    g_signal_connect((gpointer) login_window, "delete_event",
                     G_CALLBACK(on_window_delete_event), NULL);
    g_signal_connect((gpointer) entry_account_name, "activate",
                     G_CALLBACK(on_entry_account_name_activate), NULL);
    g_signal_connect((gpointer) entry_account_password, "activate",
                     G_CALLBACK(on_entry_account_password_activate), NULL);
    g_signal_connect((gpointer) button_login, "clicked",
                     G_CALLBACK(on_button_login_clicked), NULL);
    g_signal_connect((gpointer) button_create_account, "clicked",
                     G_CALLBACK(on_button_create_account_clicked), NULL);
    g_signal_connect((gpointer) button_go_metaserver, "clicked",
                     G_CALLBACK(on_button_go_metaserver_clicked), NULL);
    g_signal_connect((gpointer) button_exit_client, "clicked",
                     G_CALLBACK(on_button_exit_client_clicked), NULL);
}
