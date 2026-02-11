parse_upload(struct dlist *kr, struct mailbox *mailbox,
			struct index_record *record)
{
    struct dlist *fl;
    const char *guid;
    int r;

    memset(record, 0, sizeof(struct index_record));

    if (!dlist_getnum(kr, "UID", &record->uid))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getmodseq(kr, "MODSEQ", &record->modseq))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getdate(kr, "LAST_UPDATED", &record->last_updated))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getlist(kr, "FLAGS", &fl))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getdate(kr, "INTERNALDATE", &record->internaldate))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getnum(kr, "SIZE", &record->size))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getatom(kr, "GUID", &guid))
	return IMAP_PROTOCOL_BAD_PARAMETERS;


    r = sync_getflags(fl, mailbox, record);
    if (r) return r;


    if (!message_guid_decode(&record->guid, guid))
	return IMAP_PROTOCOL_BAD_PARAMETERS;

    return 0;
}
