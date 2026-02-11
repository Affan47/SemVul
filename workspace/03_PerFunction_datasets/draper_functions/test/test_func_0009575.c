set_selected_files (GList * files) {
    GList * llist;
    song * s;

    if (!files)
        return;

    for (llist = g_list_first(gjay->selected_files);
         llist;
         llist = g_list_next(llist)) {
        g_free(llist->data);
    }
    g_list_free(gjay->selected_files);
    g_list_free(gjay->selected_songs);
    gjay->selected_songs = NULL;
    gjay->selected_files = NULL;

    for (llist = g_list_first(files); llist; llist = g_list_next(llist)) {
        if (g_hash_table_lookup(gjay->not_song_hash, llist->data)) {
            g_free(llist->data);
        } else {
            s = g_hash_table_lookup(gjay->song_name_hash, llist->data);
            if (!s) {


                g_free(llist->data);
            } else {
                if (s->freq_pixbuf) {
                    gdk_pixbuf_unref(s->freq_pixbuf);
                    s->freq_pixbuf = NULL;
                }
                gjay->selected_songs = g_list_append(gjay->selected_songs, s);
                gjay->selected_files = g_list_append(gjay->selected_files, llist->data);
            }
        }
    }

    gtk_widget_show(play);
    gtk_widget_hide(select_all_recursive);
    gtk_widget_show(icon);
    gtk_widget_show(vbox_lower);
    gtk_label_set_text(GTK_LABEL(label_type), "Contains...");
    gtk_image_set_from_pixbuf (GTK_IMAGE(icon), gjay->pixbufs[PM_ICON_OPEN]);
    update_selection_area();
}
