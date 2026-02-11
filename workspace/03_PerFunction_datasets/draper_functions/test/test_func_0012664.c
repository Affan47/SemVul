xdmcp_accept_cb (XDMCPClient *client, XDMCPAccept *message)
{
    status_notify ("%s GOT-ACCEPT SESSION-ID=%d AUTHENTICATION-NAME=\"%s\" AUTHORIZATION-NAME=\"%s\"", id, message->session_id, message->authentication_name, message->authorization_name);


    if (strcmp (message->authorization_name, "MIT-MAGIC-COOKIE-1") != 0)
        return;

    g_free (xdmcp_cookie);
    xdmcp_cookie_length = message->authorization_data_length;
    xdmcp_cookie = g_malloc (message->authorization_data_length);
    memcpy (xdmcp_cookie, message->authorization_data, message->authorization_data_length);

    status_notify ("%s SEND-MANAGE SESSION-ID=%d DISPLAY-NUMBER=%d DISPLAY-CLASS=\"%s\"", id, message->session_id, display_number, "DISPLAY CLASS");
    xdmcp_client_send_manage (client, message->session_id, display_number, "DISPLAY CLASS");
}
