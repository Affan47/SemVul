seat_real_stop (Seat *seat)
{
    GList *list, *link;

    check_stopped (seat);
    if (seat->priv->stopped)
        return;


    list = g_list_copy (seat->priv->display_servers);
    for (link = list; link; link = link->next)
        g_object_ref (link->data);
    for (link = list; link; link = link->next)
    {
        DisplayServer *display_server = link->data;
        if (!display_server_get_is_stopping (display_server))
        {
            l_debug (seat, "Stopping display server");
            display_server_stop (display_server);
        }
    }
    g_list_free_full (list, g_object_unref);
    list = g_list_copy (seat->priv->sessions);
    for (link = list; link; link = link->next)
        g_object_ref (link->data);
    for (link = list; link; link = link->next)
    {
        Session *session = link->data;
        if (!session_get_is_stopping (session))
        {
            l_debug (seat, "Stopping session");
            session_stop (session);
        }
    }
    g_list_free_full (list, g_object_unref);
}
