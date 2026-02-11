deliver(message_data_t *msg)
{
    int n, r = 0, myrights;
    char *rcpt = NULL, *local_rcpt = NULL, *server, *acl;
    unsigned long uid;
    struct body *body = NULL;
    struct dest *dlist = NULL;
    duplicate_key_t dkey = {msg->id, NULL, msg->date};


    for (n = 0; n < msg->rcpt_num; n++) {
	rcpt = msg->rcpt[n];


	r = mlookup(rcpt, &server, &acl, NULL);
	dkey.to = rcpt;
	if (r) return IMAP_MAILBOX_NONEXISTENT;

	if (!(acl && (myrights = cyrus_acl_myrights(nntp_authstate, acl)) &&
	      (myrights & ACL_POST)))
	    return IMAP_PERMISSION_DENIED;

	if (server) {

	    proxy_adddest(&dlist, NULL, 0, server, "");
	}
	else {

	    struct appendstate as;

	    if (msg->id &&
		duplicate_check(&dkey)) {

		duplicate_log(&dkey, "nntp delivery");
		continue;
	    }

	    r = append_setup(&as, rcpt,
			     nntp_authstate ? nntp_userid : NULL,
			     nntp_authstate, ACL_POST, 0);

	    if (!r) {
		prot_rewind(msg->data);
		if (stage) {
		    r = append_fromstage(&as, &body, stage, 0,
					 (const char **) NULL, 0, !singleinstance);
		} else {

		    r = append_fromstream(&as, &body, msg->data, msg->size, 0,
					  (const char **) NULL, 0);
		}
		if (r || ( msg->id && duplicate_check(&dkey) ) ) {
		    append_abort(&as);

		    if (!r) {

			duplicate_log(&dkey, "nntp delivery");
			continue;
		    }
		}
		else {
		    r = append_commit(&as, 0, NULL, &uid, NULL, NULL);
		}
	    }

	    if (!r && msg->id)
		duplicate_mark(&dkey, time(NULL), uid);

	    if (r) return r;

	    local_rcpt = rcpt;
	}
    }

    if (body) {
	message_free_body(body);
	free(body);
    }

    if (dlist) {
	struct dest *d;


	r = deliver_remote(msg, dlist);


	d = dlist;
	while (d) {
	    struct dest *nextd = d->next;
	    free(d);
	    d = nextd;
	}
    }

    return r;
}
