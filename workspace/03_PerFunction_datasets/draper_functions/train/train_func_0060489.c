init_mbox( struct mbox_struct ** mb ) {
	struct mbox_struct * new_mbox;
	new_mbox = (struct mbox_struct *) malloc(sizeof(struct mbox_struct));
	if ( ! new_mbox ) {
		printf("asmail: failed to allocate memory for the mailbox control structure.\n");
		return(-1);
	}
	if ( pthread_mutex_init(&new_mbox->mutex, NULL) ) {
		printf("asmail: parse_cfg_mbox: failed to initialize mutex.\n");
		return(-1);
	}
	new_mbox->type = 0;
	strcpy(new_mbox->file, "");
	strcpy(new_mbox->server, "");
	strcpy(new_mbox->user, "");
	strcpy(new_mbox->pass, "");
	strcpy(new_mbox->mbox, "");
	new_mbox->auth = AUTH_PLAIN | AUTH_MD5;
	new_mbox->port = 0;
	new_mbox->timeout = 60;
	new_mbox->update = 10;
	new_mbox->flags = FLAG_DEFAULT;
	new_mbox->status = STAT_IDLE;
	new_mbox->mail = MAIL_NONE;
	new_mbox->ctotal = 0;
	new_mbox->cnew = 0;
#ifdef HAVE_OPENSSL_SSL_H
	strcpy(new_mbox->trustedCaDir, "");
#endif
	new_mbox->next = NULL;
	*mb = new_mbox;
	return(0);
}
