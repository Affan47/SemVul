seat_unity_create_greeter_session (Seat *seat)
{
    Greeter *greeter_session;
    gchar *id;
    gint vt;

    greeter_session = SEAT_CLASS (seat_unity_parent_class)->create_greeter_session (seat);
    session_set_env (SESSION (greeter_session), "XDG_SEAT", seat_get_name (seat));

    id = g_strdup_printf ("greeter-%d", SEAT_UNITY (seat)->priv->next_greeter_id);
    SEAT_UNITY (seat)->priv->next_greeter_id++;
    session_set_env (SESSION (greeter_session), "MIR_SERVER_NAME", id);
    g_free (id);

    vt = display_server_get_vt (DISPLAY_SERVER (SEAT_UNITY (seat)->priv->compositor));
    if (vt >= 0)
    {
        gchar *value = g_strdup_printf ("%d", vt);
        session_set_env (SESSION (greeter_session), "XDG_VTNR", value);
        g_free (value);
    }

    return greeter_session;
}
