handle_set_language (Greeter *greeter, const gchar *language)
{
    User *user;

    if (!greeter->priv->guest_account_authenticated && !session_get_is_authenticated (greeter->priv->authentication_session))
    {
        l_debug (greeter, "Ignoring set language request, user is not authorized");
        return;
    }


    if (greeter->priv->guest_account_authenticated)
    {
        l_debug (greeter, "Ignoring set language request for guest user");
        return;
    }

    l_debug (greeter, "Greeter sets language %s", language);
    user = session_get_user (greeter->priv->authentication_session);
    user_set_language (user, language);
}
