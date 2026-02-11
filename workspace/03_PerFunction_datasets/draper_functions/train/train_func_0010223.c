log_file_done(struct log_file *f, int do_sync)
{
	if (f->fd < 0) return;

	if (do_sync)
		log_file_fsync(f);
	else
		log_file_flush(f);
	if (close(f->fd)) pexit("close");
	f->fd = -1;

	MEM_FREE(f->buffer);
}
