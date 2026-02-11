display_manager_add_seat (DisplayManager *manager, Seat *seat)
{
    gboolean result;

    g_return_val_if_fail (!manager->priv->stopping, FALSE);

    result = seat_start (SEAT (seat));
    if (!result)
        return FALSE;

    manager->priv->seats = g_list_append (manager->priv->seats, g_object_ref (seat));
    g_signal_connect (seat, "stopped", G_CALLBACK (seat_stopped_cb), manager);
    g_signal_emit (manager, signals[SEAT_ADDED], 0, seat);

    return TRUE;
}
