parent_set_callback (GtkWidget *widget,
                                 gpointer user_data) {
    song * s;
    GList * ll;
    gint num_songs;
    gboolean is_dir;

    gtk_widget_hide(button_sel_songs);
    gtk_widget_hide(button_sel_dir);
    gtk_widget_hide(button_start_song);

    num_songs = 0;
    is_dir = FALSE;

    if (!gjay->selected_songs && gjay->selected_files) {
        is_dir = TRUE;
    } else if (gjay->selected_songs) {
        for (ll = g_list_first(gjay->selected_songs);
             ll && (num_songs < 2); ll = g_list_next(ll)) {
            s = (song *) ll->data;
            if (!s->no_data)
                num_songs++;
        }
    }

    if (is_dir) {
        gtk_widget_show(button_sel_dir);
        gjay->prefs->use_selected_songs = FALSE;
        gjay->prefs->start_selected = FALSE;
    } else if (num_songs == 1) {

        gtk_widget_show(button_start_song);
        gjay->prefs->use_selected_dir = FALSE;
        gjay->prefs->use_selected_songs = FALSE;
    } else if (num_songs > 1) {

        gtk_widget_show(button_sel_songs);
        gjay->prefs->use_selected_dir = FALSE;
        gjay->prefs->start_selected = FALSE;
    } else {

        gjay->prefs->use_selected_songs = FALSE;
        gjay->prefs->use_selected_dir = FALSE;
        gjay->prefs->start_selected = FALSE;
    }

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_sel_songs),
                                 gjay->prefs->use_selected_songs);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_sel_dir),
                                 gjay->prefs->use_selected_dir);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_start_song),
                                 gjay->prefs->start_selected);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_start_color),
                                 gjay->prefs->start_color);

    if (gjay->prefs->start_selected && gjay->prefs->start_color) {
        gjay->prefs->start_color = FALSE;
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_start_color),
                                     gjay->prefs->start_color);
    }
}
