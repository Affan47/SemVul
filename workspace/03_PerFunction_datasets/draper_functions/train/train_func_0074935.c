pam_conv_cb (int msg_length, const struct pam_message **msg, struct pam_response **resp, void *app_data)
{
    int i, error;
    gboolean auth_complete = FALSE;
    struct pam_response *response;
    gchar *username = NULL;


    if (authentication_complete)
        return PAM_SUCCESS;


    if (!is_interactive)
    {
        for (i = 0; i < msg_length; i++)
        {
            if (msg[i]->msg_style == PAM_PROMPT_ECHO_ON || msg[i]->msg_style == PAM_PROMPT_ECHO_OFF)
            {
                g_printerr ("Stopping PAM conversation, interaction requested but not supported\n");
                return PAM_CONV_ERR;
            }
        }


        return PAM_SUCCESS;
    }


    pam_get_item (pam_handle, PAM_USER, (const void **) &username);


    write_string (username);
    write_data (&auth_complete, sizeof (auth_complete));
    write_data (&msg_length, sizeof (msg_length));
    for (i = 0; i < msg_length; i++)
    {
        const struct pam_message *m = msg[i];
        write_data (&m->msg_style, sizeof (m->msg_style));
        write_string (m->msg);
    }


    read_data (&error, sizeof (error));
    if (error != PAM_SUCCESS)
        return error;
    response = calloc (msg_length, sizeof (struct pam_response));
    for (i = 0; i < msg_length; i++)
    {
        struct pam_response *r = &response[i];


        r->resp = read_string_full (malloc);
        read_data (&r->resp_retcode, sizeof (r->resp_retcode));
    }

    *resp = response;
    return PAM_SUCCESS;
}
