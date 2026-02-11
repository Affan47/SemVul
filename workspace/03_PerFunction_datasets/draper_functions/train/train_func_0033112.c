lightdm_greeter_cancel_authentication (LightDMGreeter *greeter)
{
    LightDMGreeterPrivate *priv;
    guint8 message[MAX_MESSAGE_LENGTH];
    gsize offset = 0;

    g_return_if_fail (LIGHTDM_IS_GREETER (greeter));

    priv = GET_PRIVATE (greeter);

    g_return_if_fail (priv->connected);

    priv->cancelling_authentication = TRUE;
    write_header (message, MAX_MESSAGE_LENGTH, GREETER_MESSAGE_CANCEL_AUTHENTICATION, 0, &offset);
    write_message (greeter, message, offset);
}
