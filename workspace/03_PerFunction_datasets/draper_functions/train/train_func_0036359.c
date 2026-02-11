watcher_check_mtime(void *value, void *unused_udata)
{
	struct monitored *m = value;
	time_t new_mtime;

	(void) unused_udata;

	new_mtime = watcher_mtime(m->filename);

	if (new_mtime > m->mtime) {
		m->mtime = new_mtime;
		(*m->cb)(m->filename, m->udata);
	}
}
