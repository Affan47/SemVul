gnc_dialog_query_view_button_clicked (GtkButton *button, DialogQueryView *dqv)
{
    GNCDisplayViewButton *cb;
    gpointer entry;

    g_return_if_fail (dqv);
    entry = gnc_query_view_get_selected_entry (GNC_QUERY_VIEW (dqv->qview));
    if (!entry)
        return;

    cb = g_object_get_data (G_OBJECT (button), "data");
    g_return_if_fail (cb);

    gnc_dialog_query_run_callback (cb, entry, dqv);
}
