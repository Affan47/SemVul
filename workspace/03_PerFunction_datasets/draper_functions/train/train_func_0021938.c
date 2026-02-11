do_getfullmailbox(struct dlist *kin)
{
    struct mailbox *mailbox = NULL;
    struct dlist *kl = dlist_kvlist(NULL, "MAILBOX");
    int r;

    r = mailbox_open_irl(kin->sval, &mailbox);
    if (r) return r;

    r = sync_mailbox(mailbox, NULL, NULL, kl, NULL, 1);
    if (!r) sync_send_response(kl, sync_out);
    dlist_free(&kl);
    mailbox_close(&mailbox);

    return r;
}
