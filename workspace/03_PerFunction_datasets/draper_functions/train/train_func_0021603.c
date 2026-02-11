session_respond (Session *session, struct pam_response *response)
{
    int error = PAM_SUCCESS;
    int i;

    g_return_if_fail (session != NULL);

    write_data (session, &error, sizeof (error));
    for (i = 0; i < session->priv->messages_length; i++)
    {
        write_string (session, response[i].resp);
        write_data (session, &response[i].resp_retcode, sizeof (response[i].resp_retcode));
    }


    for (i = 0; i < session->priv->messages_length; i++)
        g_free ((char *) session->priv->messages[i].msg);
    g_free (session->priv->messages);
    session->priv->messages = NULL;
    session->priv->messages_length = 0;
}
