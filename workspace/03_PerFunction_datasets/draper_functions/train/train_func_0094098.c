do_rename(struct dlist *kin)
{
    const char *oldmboxname;
    const char *newmboxname;
    const char *partition;

    if (!dlist_getatom(kin, "OLDMBOXNAME", &oldmboxname))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getatom(kin, "NEWMBOXNAME", &newmboxname))
	return IMAP_PROTOCOL_BAD_PARAMETERS;
    if (!dlist_getatom(kin, "PARTITION", &partition))
	return IMAP_PROTOCOL_BAD_PARAMETERS;

    return mboxlist_renamemailbox(oldmboxname, newmboxname, partition,
                                  1, sync_userid, sync_authstate, 1, 1);
}
