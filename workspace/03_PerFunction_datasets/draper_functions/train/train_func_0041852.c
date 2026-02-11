fixquota_mailbox(void *rock __attribute__((unused)),
			    const char *name, int namelen,
			    const char *val __attribute__((unused)),
			    int vallen __attribute__((unused)))
{
    int r = 0;
    struct mailbox *mailbox = NULL;
    int thisquota = -1;
    char *mboxname = xstrndup(name, namelen);

    r = findroot(mboxname, &thisquota);
    if (r) {
	errmsg("failed finding quotaroot for mailbox '%s'", name, r);
	goto done;
    }

    r = mailbox_open_iwl(mboxname, &mailbox);
    if (r) {
	errmsg("failed opening header for mailbox '%s'", name, r);
	goto done;
    }

    if (thisquota == -1) {


	if (mailbox->quotaroot) {
	    r = fixquota_fixroot(mailbox, (char *)0);
	}
    }
    else {


	if (!mailbox->quotaroot ||
	    strcmp(mailbox->quotaroot, quota[thisquota].quota.root) != 0) {
	    r = fixquota_fixroot(mailbox, quota[thisquota].quota.root);
	}


	if (!r)
	    quota[thisquota].newused += mailbox->i.quota_mailbox_used;
    }

done:
    mailbox_close(&mailbox);
    free(mboxname);

    return r;
}
