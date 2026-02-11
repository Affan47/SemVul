flush(struct sha1file *f, unsigned int count)
{
	void *buf = f->buffer;

	for (;;) {
		int ret = xwrite(f->fd, buf, count);
		if (ret > 0) {
			f->total += ret;
			display_throughput(f->tp, f->total);
			buf = (char *) buf + ret;
			count -= ret;
			if (count)
				continue;
			return;
		}
		if (!ret)
			die("sha1 file '%s' write error. Out of diskspace", f->name);
		die("sha1 file '%s' write error (%s)", f->name, strerror(errno));
	}
}
