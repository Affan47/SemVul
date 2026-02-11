button_press_callback (GtkWidget *widget, GdkEventFocus *event, gpointer user_data)
{
    NemoIconView *view = NEMO_ICON_VIEW (user_data);

    if (!nemo_view_get_active (NEMO_VIEW (view))) {
        NemoWindowSlot *slot = nemo_view_get_nemo_window_slot (NEMO_VIEW (view));
        nemo_window_slot_make_hosting_pane_active (slot);
        return TRUE;
    }

    return FALSE;
}
