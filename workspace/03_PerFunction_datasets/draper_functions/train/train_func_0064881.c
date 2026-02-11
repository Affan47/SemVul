log_file_fsync(struct log_file *f)
{
	if (f->fd < 0) return;

	log_file_flush(f);
#ifndef __CYGWIN32__
	if (fsync(f->fd)) pexit("fsync");
#endif
}
