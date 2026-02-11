log_debug_enabled(void)
{
	mowgli_node_t *n;
	logfile_t *lf;

	if (log_force)
		return true;
	MOWGLI_ITER_FOREACH(n, log_files.head)
	{
		lf = n->data;
		if (lf->log_mask & (LG_DEBUG | LG_RAWDATA))
			return true;
	}
	return false;
}
