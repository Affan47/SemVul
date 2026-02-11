log_fini(void)
{
	if (!log)
		return;

	slurm_mutex_lock(&log_lock);
	_log_flush(log);
	xfree(log->argv0);
	xfree(log->fpfx);
	if (log->buf)
		cbuf_destroy(log->buf);
	if (log->fbuf)
		cbuf_destroy(log->fbuf);
	if (log->logfp)
		fclose(log->logfp);
	xfree(log);
	xfree(slurm_prog_name);
	slurm_mutex_unlock(&log_lock);
}
