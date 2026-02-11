imap_close_server(struct imap_store *ictx)
{
	struct imap *imap = ictx->imap;

	if (imap->buf.sock.fd != -1) {
		imap_exec(ictx, NULL, "LOGOUT");
		socket_shutdown(&imap->buf.sock);
	}
	free_list(imap->ns_personal);
	free_list(imap->ns_other);
	free_list(imap->ns_shared);
	free(imap);
}
