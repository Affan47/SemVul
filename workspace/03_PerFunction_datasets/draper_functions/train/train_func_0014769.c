greeter_stop (Session *session)
{
    Greeter *greeter = GREETER (session);


    if (greeter->priv->authentication_session)
        g_signal_handlers_disconnect_matched (greeter->priv->authentication_session, G_SIGNAL_MATCH_DATA, 0, 0, NULL, NULL, greeter);

    SESSION_CLASS (greeter_parent_class)->stop (session);
}
