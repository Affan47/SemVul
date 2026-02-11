send_info (pam_handle_t *pamh, const char *message)
{
    struct pam_message **msg;
    struct pam_response *resp = NULL;

    msg = calloc (1, sizeof (struct pam_message *));
    msg[0] = malloc (sizeof (struct pam_message));
    msg[0]->msg_style = PAM_TEXT_INFO;
    msg[0]->msg = message;
    pamh->conversation.conv (1, (const struct pam_message **) msg, &resp, pamh->conversation.appdata_ptr);
    free (msg[0]);
    free (msg);
    if (resp)
    {
        if (resp[0].resp)
            free (resp[0].resp);
        free (resp);
    }
}
