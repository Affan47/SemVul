email_login(HybridAccount *account)
{
    hybrid_imap *imap;

    if (!(imap = hybrid_imap_create(account))) {
        hybrid_account_error_reason(account,
                                    "Username must be a valid email address.");
        return FALSE;
    }

    hybrid_account_set_protocol_data(account, imap);

    hybrid_debug_info("imap", "connecting to imap server %s:%d",
                      imap->imap_server, imap->imap_port);

    hybrid_account_set_connection_string(account,
                                         _("Connecting to IMAP server."));

    hybrid_ssl_connect(imap->imap_server,
                       imap->imap_port,
                       SSL_CALLBACK(ssl_connect_cb),
                       imap);

    return TRUE;
}
