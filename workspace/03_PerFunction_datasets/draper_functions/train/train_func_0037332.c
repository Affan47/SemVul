create_playlist_file(GtkWidget *w, gpointer data)
{
    if (!gtkpod_has_exporter())
        return;

    Exporter *exporter = gtkpod_get_exporter();

    if(gtkpod_get_selected_tracks())
        exporter_export_tracks_to_playlist_file(exporter, gtkpod_get_selected_tracks());
}
