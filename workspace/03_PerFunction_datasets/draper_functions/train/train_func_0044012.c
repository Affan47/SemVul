spl_liveupdate_toggled(GtkToggleButton *togglebutton, GtkWidget *spl_window) {
    Playlist *spl;

    g_return_if_fail (spl_window);
    spl = g_object_get_data(G_OBJECT (spl_window), "spl_work");
    g_return_if_fail (spl);
    spl->splpref.liveupdate = gtk_toggle_button_get_active(togglebutton);
}
