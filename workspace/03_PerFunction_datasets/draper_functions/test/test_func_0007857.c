mutex_grab_from(mutex_t *m, bool hidden, const char *file, unsigned line)
{
	mutex_grab(m, hidden);

	if (1 == m->depth) {
		m->lock.file = file;
		m->lock.line = line;
	}
}
