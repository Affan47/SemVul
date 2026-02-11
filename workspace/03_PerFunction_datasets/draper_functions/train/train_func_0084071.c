maildir_trash_msg( store_t *gctx, message_t *gmsg,
                   void (*cb)( int sts, void *aux ), void *aux )
{
	maildir_store_t *ctx = (maildir_store_t *)gctx;
	maildir_message_t *msg = (maildir_message_t *)gmsg;
	char *s;
	int ret;
	struct stat st;
	char buf[_POSIX_PATH_MAX], nbuf[_POSIX_PATH_MAX];

	for (;;) {
		nfsnprintf( buf, sizeof(buf), "%s/%s/%s", gctx->path, subdirs[gmsg->status & M_RECENT], msg->base );
		s = strstr( msg->base, ":2," );
		nfsnprintf( nbuf, sizeof(nbuf), "%s/%s/%ld.%d_%d.%s%s", ctx->trash,
		            subdirs[gmsg->status & M_RECENT], (long)time( 0 ), Pid, ++MaildirCount, Hostname, s ? s : "" );
		if (!rename( buf, nbuf ))
			break;
		if (!stat( buf, &st )) {
			if ((ret = maildir_validate( ctx->trash, 1, ctx )) != DRV_OK) {
				cb( ret, aux );
				return;
			}
			if (!rename( buf, nbuf ))
				break;
			if (errno != ENOENT) {
				sys_error( "Maildir error: cannot move %s to %s", buf, nbuf );
				cb( DRV_BOX_BAD, aux );
				return;
			}
		}
		if ((ret = maildir_again( ctx, msg, "Maildir error: cannot move %s to %s", buf, nbuf )) != DRV_OK) {
			cb( ret, aux );
			return;
		}
	}
	gmsg->status |= M_DEAD;
	gctx->count--;

#ifdef USE_DB
	if (ctx->db) {
		cb( maildir_purge_msg( ctx, msg->base ), aux );
		return;
	}
#endif
	cb( DRV_OK, aux );
}
