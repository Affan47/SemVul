d_step_copy(struct bgtask *h, void *u, int ticks)
{
	struct moved *md = u;
	ssize_t r;
	size_t amount;
	filesize_t remain;
	int used = 0;
	int t;

	g_assert(md->magic == MOVED_MAGIC);

	if (NULL == md->rd)
		return BGR_DONE;

	if (md->size == 0)
		return BGR_DONE;

again:

	g_assert(md->size > md->copied);
	remain = md->size - md->copied;
	remain = MIN(remain, COPY_BUF_SIZE);


	amount = MAX(0, ticks);
	amount = size_saturate_mult(amount, COPY_BLOCK_FRAGMENT);
	amount = MIN(amount, remain);

	g_assert(amount > 0);

	r = file_object_pread(md->rd, md->buffer, amount, md->copied);
	if ((ssize_t) -1 == r) {
		md->error = errno;
		g_warning("error while reading \"%s\" for moving: %m",
			file_object_get_pathname(md->rd));
		return BGR_DONE;
	} else if (r == 0) {
		g_warning("EOF while reading \"%s\" for moving!",
			file_object_get_pathname(md->rd));
		md->error = -1;
		return BGR_DONE;
	}

	g_assert((size_t) r == amount);


	t = (r / COPY_BLOCK_FRAGMENT) + (r % COPY_BLOCK_FRAGMENT ? 1 : 0);
	used += t;

	bg_task_ticks_used(h, used);

	r = write(md->wd, md->buffer, amount);
	if ((ssize_t) -1 == r) {
		md->error = errno;
		g_warning("error while writing for moving \"%s\": %m",
			download_basename(md->d));
		return BGR_DONE;
	} else if ((size_t) r < amount) {
		md->error = -1;
		g_warning("short write whilst moving \"%s\"", download_basename(md->d));
		return BGR_DONE;
	}

	g_assert((size_t) r == amount);

	md->copied += r;
	download_move_progress(md->d, md->copied);

	if (md->copied == md->size)
		return BGR_DONE;


	ticks -= t;
	if (ticks > 0)
		goto again;

	return BGR_MORE;
}
