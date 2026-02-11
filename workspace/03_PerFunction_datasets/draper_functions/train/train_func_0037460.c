pam_chauthtok (pam_handle_t *pamh, int flags)
{
    struct passwd *entry;
    int result;
    struct pam_message **msg;
    struct pam_response *resp = NULL;

    if (pamh == NULL)
        return PAM_SYSTEM_ERR;

    if (strcmp (pamh->user, "log-pam") == 0)
        send_info (pamh, "pam_chauthtok");

    msg = malloc (sizeof (struct pam_message *) * 1);
    msg[0] = malloc (sizeof (struct pam_message));
    msg[0]->msg_style = PAM_PROMPT_ECHO_OFF;
    if ((flags & PAM_CHANGE_EXPIRED_AUTHTOK) != 0)
        msg[0]->msg = "Enter new password (expired):";
    else
        msg[0]->msg = "Enter new password:";
    result = pamh->conversation.conv (1, (const struct pam_message **) msg, &resp, pamh->conversation.appdata_ptr);
    free (msg[0]);
    free (msg);
    if (result != PAM_SUCCESS)
        return result;

    if (resp == NULL)
        return PAM_CONV_ERR;
    if (resp[0].resp == NULL)
    {
        free (resp);
        return PAM_CONV_ERR;
    }


    entry = getpwnam (pamh->user);
    free (entry->pw_passwd);
    entry->pw_passwd = resp[0].resp;
    free (resp);

    return PAM_SUCCESS;
}
