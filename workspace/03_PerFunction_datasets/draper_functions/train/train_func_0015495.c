details_button_next_clicked(GtkCheckButton *button) {
    GList *gl;
    g_return_if_fail (details_view);

    details_get_changes();

    gl = g_list_find(details_view->tracks, details_view->track);

    g_return_if_fail (gl);

    if (gl->next)
        details_set_track(gl->next->data);
}
