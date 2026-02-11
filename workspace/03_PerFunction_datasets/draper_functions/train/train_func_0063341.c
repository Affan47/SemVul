dothreadreferences(struct searchinfo *si, struct searchinfo *sihead,
			const char *charset,
			int isuid)
{
	struct imap_refmsgtable *reftable;
	struct imap_refmsg *root;

	if (!(reftable=rfc822_threadalloc()))
	{
		write_error_exit(0);
		return;
	}

	search_internal(si, sihead, charset, 0,
			thread_ref_callback, reftable);

	root=rfc822_thread(reftable);
	printthread(root, isuid);
	rfc822_threadfree(reftable);
}
