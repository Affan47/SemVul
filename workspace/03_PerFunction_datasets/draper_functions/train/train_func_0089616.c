imap_trash_msg( store_t *gctx, message_t *msg,
                void (*cb)( int sts, void *aux ), void *aux )
{
	imap_store_t *ctx = (imap_store_t *)gctx;
	struct imap_cmd_simple *cmd;
	char *buf;

	INIT_IMAP_CMD(imap_cmd_simple, cmd, cb, aux)
	cmd->gen.param.create = 1;
	cmd->gen.param.to_trash = 1;
	if (prepare_trash( &buf, ctx ) < 0) {
		cb( DRV_BOX_BAD, aux );
		return;
	}
	imap_exec( ctx, &cmd->gen, imap_done_simple_msg,
	           CAP(MOVE) ? "UID MOVE %d \"%\\s\"" : "UID COPY %d \"%\\s\"", msg->uid, buf );
	free( buf );
}
