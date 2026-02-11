log_stat(enum log_file which, struct logstat *buf)
{
	struct logfile *lf;

	log_file_check(which);
	g_assert(buf != NULL);

	lf = &logfile[which];
	buf->name = lf->name;
	buf->path = lf->path;
	buf->otime = lf->otime;
	buf->disabled = lf->disabled;
	buf->need_reopen = lf->changed;

	{
		filestat_t sbuf;

		fflush(lf->f);

		if (-1 == fstat(fileno(lf->f), &sbuf)) {
			s_warning("cannot stat logfile \"%s\" at \"%s\": %m",
				lf->name, lf->path);
			buf->size = 0;
		} else
			buf->size = sbuf.st_size;
	}
}
