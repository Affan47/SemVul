check_mail(gpointer user_data)
{
    hybrid_imap *imap;
    gchar       *cmd;

    imap = (hybrid_imap*)user_data;

    cmd = g_strdup_printf("A%d STATUS INBOX (UNSEEN)\r\n",
                          imap->current_tag);

    hybrid_debug_info("imap", "send:\n%s", cmd);

    imap_trans_create(imap, check_mail_cb, NULL);

    if (hybrid_ssl_write(imap->ssl, cmd, strlen(cmd)) <= 0) {
        hybrid_account_error_reason(imap->account,
                                    _("IMAP Connection Closed."));
    }

    g_free(cmd);

    if (imap->mail_check_source > 0) {
        g_source_remove(imap->mail_check_source);
        imap->mail_check_source = 0;
    }

    return FALSE;
}
