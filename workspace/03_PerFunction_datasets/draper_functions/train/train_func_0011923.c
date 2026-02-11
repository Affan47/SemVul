switch_authentication_complete_cb (Session *session, Seat *seat)
{
    Greeter *greeter_session;
    DisplayServer *display_server;


    if (session_get_is_authenticated (session))
    {
        Session *s;

        s = find_user_session (seat, session_get_username (session), session);
        if (s)
        {
            l_debug (seat, "Session authenticated, switching to existing user session");
            session_unlock (s);
            seat_set_active_session (seat, s);
            session_stop (session);
        }
        else
        {
            l_debug (seat, "Session authenticated, starting display server");
            if (seat->priv->session_to_activate)
                g_object_unref (seat->priv->session_to_activate);
            seat->priv->session_to_activate = g_object_ref (session);
            display_server = create_display_server (seat, session);
            session_set_display_server (session, display_server);
            display_server_start (display_server);
        }

        return;
    }

    l_debug (seat, "Switching to greeter to authenticate session");

    session_stop (session);

    greeter_session = create_greeter_session (seat);
    if (session_get_is_guest (session))
        greeter_set_hint (greeter_session, "select-guest", "true");
    else
        greeter_set_hint (greeter_session, "select-user", session_get_username (session));
    if (seat->priv->session_to_activate)
        g_object_unref (seat->priv->session_to_activate);
    seat->priv->session_to_activate = g_object_ref (greeter_session);

    display_server = create_display_server (seat, SESSION (greeter_session));
    session_set_display_server (SESSION (greeter_session), display_server);
    display_server_start (display_server);
}
