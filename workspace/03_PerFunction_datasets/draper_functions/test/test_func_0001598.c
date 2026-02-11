maildir_rescan( maildir_store_t *ctx )
{
	message_t **msgapp;
	maildir_message_t *msg;
	msglist_t msglist;
	int i;

	if (maildir_scan( ctx, &msglist ) != DRV_OK)
		return DRV_BOX_BAD;
	ctx->gen.recent = 0;
	for (msgapp = &ctx->gen.msgs, i = 0;
	     (msg = (maildir_message_t *)*msgapp) || i < msglist.nents; )
	{
		if (!msg) {
#if 0
			debug( "adding new message %d\n", msglist.ents[i].uid );
			maildir_app_msg( ctx, &msgapp, msglist.ents + i );
#else
			debug( "ignoring new message %d\n", msglist.ents[i].uid );
#endif
			i++;
		} else if (i >= msglist.nents) {
			debug( "purging deleted message %d\n", msg->gen.uid );
			msg->gen.status = M_DEAD;
			msgapp = &msg->gen.next;
		} else if (msglist.ents[i].uid < msg->gen.uid) {

#if 0
			debug( "adding new message %d\n", msglist.ents[i].uid );
			maildir_app_msg( ctx, &msgapp, msglist.ents + i );
#else
			debug( "ignoring new message %d\n", msglist.ents[i].uid );
#endif
			i++;
		} else if (msglist.ents[i].uid > msg->gen.uid) {
			debug( "purging deleted message %d\n", msg->gen.uid );
			msg->gen.status = M_DEAD;
			msgapp = &msg->gen.next;
		} else {
			debug( "updating message %d\n", msg->gen.uid );
			msg->gen.status &= ~(M_FLAGS|M_RECENT);
			free( msg->base );
			maildir_init_msg( ctx, msg, msglist.ents + i );
			i++, msgapp = &msg->gen.next;
		}
	}
	maildir_free_scan( &msglist );
	return DRV_OK;
}
