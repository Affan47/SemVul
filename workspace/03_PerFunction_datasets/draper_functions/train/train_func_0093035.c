details_text_changed(GtkWidget *widget) {
    ExtraTrackData *etr;

    g_return_if_fail (details_view);
    g_return_if_fail (details_view->track);
    etr = details_view->track->userdata;
    g_return_if_fail (etr);

    details_view->changed = TRUE;
    etr->tchanged = TRUE;
    details_update_buttons();
}
