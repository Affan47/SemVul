details_update_buttons() {
    GtkWidget *w;
    gchar *buf;
    ExtraTrackData *etr;
    gboolean apply, undo_track, undo_all, remove_artwork, viewport;
    gboolean prev, next;

    g_return_if_fail (details_view);

    if (details_view->track) {
        gint i;
        etr = details_view->track->userdata;
        g_return_if_fail (etr);

        details_update_changed_state();

        apply = details_view->changed;
        undo_track = etr->tchanged;
        undo_all = details_view->changed;
        viewport = TRUE;
        if (details_writethrough()) {
            GList *gl;
            remove_artwork = FALSE;
            for (gl = details_view->tracks; gl && !remove_artwork; gl = gl->next) {
                Track *tr = gl->data;
                g_return_if_fail (tr);
                remove_artwork |= itdb_track_has_thumbnails(tr);
            }
        }
        else {
            remove_artwork = (itdb_track_has_thumbnails(details_view->track));
        }
        i = g_list_index(details_view->tracks, details_view->track);
        g_return_if_fail (i != -1);
        if (i == 0)
            prev = FALSE;
        else
            prev = TRUE;
        if (i == (g_list_length(details_view->tracks) - 1))
            next = FALSE;
        else
            next = TRUE;

    }
    else {
        apply = FALSE;
        undo_track = FALSE;
        undo_all = FALSE;
        viewport = FALSE;
        remove_artwork = FALSE;
        prev = FALSE;
        next = FALSE;
    }

    w = gtkpod_builder_xml_get_widget(details_view->xml, "details_button_apply");
    gtk_widget_set_sensitive(w, apply);
    w = gtkpod_builder_xml_get_widget(details_view->xml, "details_button_undo_track");
    gtk_widget_set_sensitive(w, undo_track);
    w = gtkpod_builder_xml_get_widget(details_view->xml, "details_button_undo_all");
    gtk_widget_set_sensitive(w, undo_all);
    w = gtkpod_builder_xml_get_widget(details_view->xml, "details_button_remove_artwork");
    gtk_widget_set_sensitive(w, remove_artwork);
    w = gtkpod_builder_xml_get_widget(details_view->xml, "details_details");
    gtk_widget_set_sensitive(w, viewport);
    w = gtkpod_builder_xml_get_widget(details_view->xml, "details_button_first");
    gtk_widget_set_sensitive(w, prev);
    w = gtkpod_builder_xml_get_widget(details_view->xml, "details_button_previous");
    gtk_widget_set_sensitive(w, prev);
    w = gtkpod_builder_xml_get_widget(details_view->xml, "details_button_next");
    gtk_widget_set_sensitive(w, next);
    w = gtkpod_builder_xml_get_widget(details_view->xml, "details_button_last");
    gtk_widget_set_sensitive(w, next);

    if (details_view->track) {
        buf
                = g_strdup_printf("%d / %d", g_list_index(details_view->tracks, details_view->track) + 1, g_list_length(details_view->tracks));
    }
    else {
        buf = g_strdup(_("n/a"));
    }
    w = gtkpod_builder_xml_get_widget(details_view->xml, "details_label_index");
    gtk_label_set_text(GTK_LABEL (w), buf);
    g_free(buf);
}
