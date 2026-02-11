do_fetch(struct dlist *kin)
{
    const char *mboxname;
    const char *partition;
    const char *guid;
    uint32_t uid;
    const char *fname;
    struct dlist *kl;
    struct message_guid tmp_guid;
    struct stat sbuf;

    if (!dlist_getatom(kin, "MBOXNAME", &mboxname))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getatom(kin, "PARTITION", &partition))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getatom(kin, "GUID", &guid))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getnum(kin, "UID", &uid))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!message_guid_decode(&tmp_guid, guid))
	return IMAP_PROTOCOL_BAD_PARAMETERS;

    fname = mboxname_datapath(partition, mboxname, uid);
    if (stat(fname, &sbuf) == -1)
	return IMAP_MAILBOX_NONEXISTENT;

    kl = dlist_file(NULL, "MESSAGE", partition, &tmp_guid, sbuf.st_size, fname);
    sync_send_response(kl, sync_out);
    dlist_free(&kl);

    return 0;
}
