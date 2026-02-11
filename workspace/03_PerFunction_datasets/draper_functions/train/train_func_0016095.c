mboxlist_changesub(const char *name, const char *userid,
		       struct auth_state *auth_state, int add, int force)
{
    struct mboxlist_entry mbentry;
    int r;
    struct db *subs;

    if ((r = mboxlist_opensubs(userid, &subs)) != 0) {
	return r;
    }

    if (add && !force) {

	if ((r = mboxlist_lookup(name, &mbentry, NULL))!=0) {
	    mboxlist_closesubs(subs);
	    return r;
	}
	if ((cyrus_acl_myrights(auth_state, mbentry.acl) & ACL_LOOKUP) == 0) {
	    mboxlist_closesubs(subs);
	    return IMAP_MAILBOX_NONEXISTENT;
	}
    }

    if (add) {
	r = SUBDB->store(subs, name, strlen(name), "", 0, NULL);
    } else {
	r = SUBDB->delete(subs, name, strlen(name), NULL, 0);

	if (r == CYRUSDB_EXISTS) r = CYRUSDB_OK;
    }

    switch (r) {
    case CYRUSDB_OK:
	r = 0;
	break;

    default:
	r = IMAP_IOERROR;
	break;
    }

    sync_log_subscribe(userid, name);
    mboxlist_closesubs(subs);
    return r;
}
