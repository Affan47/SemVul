cmd_listrights(tag, name, identifier)
char *tag;
char *name;
char *identifier;
{
    char mailboxname[MAX_MAILBOX_BUFFER];
    int r, rights;
    char *acl;

    r = (*imapd_namespace.mboxname_tointernal)(&imapd_namespace, name,
					       imapd_userid, mailboxname);

    if (!r) {
	r = mlookup(tag, name, mailboxname, NULL, NULL, &acl, NULL);
    }
    if (r == IMAP_MAILBOX_MOVED) return;

    if (!r) {
	rights = cyrus_acl_myrights(imapd_authstate, acl);

	if (!rights && !imapd_userisadmin &&
	    !mboxname_userownsmailbox(imapd_userid, mailboxname)) {
	    r = IMAP_MAILBOX_NONEXISTENT;
	}
    }

    imapd_check(NULL, 0);

    if (!r) {
	struct auth_state *authstate = auth_newstate(identifier);
	char *canon_identifier;
	int implicit;
	char rightsdesc[100], optional[33];

	if (global_authisa(authstate, IMAPOPT_ADMINS))
	    canon_identifier = identifier;
	else
	    canon_identifier = canonify_userid(identifier, imapd_userid, NULL);
	auth_freestate(authstate);

	if (!canon_identifier) {
	    implicit = 0;
	}
	else if (mboxname_userownsmailbox(canon_identifier, mailboxname)) {

	    implicit = config_implicitrights;
	}
	else if (mboxname_isusermailbox(mailboxname, 1)) {

	    implicit = ACL_POST;
	}
	else {
	    implicit = 0;
	}


	cyrus_acl_masktostr(implicit ^ (canon_identifier ? ACL_FULL : 0),
			    optional);


	if (implicit) {
	    cyrus_acl_masktostr(implicit, rightsdesc);
	}
	else {
	    strcpy(rightsdesc, "\"\"");
	}

	if (*optional) {
	    int i, n = strlen(optional);
	    char *p = rightsdesc + strlen(rightsdesc);

	    for (i = 0; i < n; i++) {
		*p++ = ' ';
		*p++ = optional[i];
	    }
	    *p = '\0';
	}

	prot_printf(imapd_out, "* LISTRIGHTS ");
	prot_printastring(imapd_out, name);
	(void)prot_putc(' ', imapd_out);
	prot_printastring(imapd_out, identifier);
	prot_printf(imapd_out, " %s", rightsdesc);

	prot_printf(imapd_out, "\r\n%s OK %s\r\n", tag,
		    error_message(IMAP_OK_COMPLETED));
	return;
    }

    prot_printf(imapd_out, "%s NO %s\r\n", tag, error_message(r));
}
