ubifs_wbuf_init(struct ubifs_info *c, struct ubifs_wbuf *wbuf)
{
	size_t size;

	wbuf->buf = kmalloc(c->max_write_size, GFP_KERNEL);
	if (!wbuf->buf)
		return -ENOMEM;

	size = (c->max_write_size / UBIFS_CH_SZ + 1) * sizeof(ino_t);
	wbuf->inodes = kmalloc(size, GFP_KERNEL);
	if (!wbuf->inodes) {
		kfree(wbuf->buf);
		wbuf->buf = NULL;
		return -ENOMEM;
	}

	wbuf->used = 0;
	wbuf->lnum = wbuf->offs = -1;


	size = c->max_write_size - (c->leb_start % c->max_write_size);
	wbuf->avail = wbuf->size = size;
	wbuf->sync_callback = NULL;
	mutex_init(&wbuf->io_mutex);
	spin_lock_init(&wbuf->lock);
	wbuf->c = c;
	wbuf->next_ino = 0;

	hrtimer_init(&wbuf->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	wbuf->timer.function = wbuf_timer_callback_nolock;
	wbuf->softlimit = ktime_set(WBUF_TIMEOUT_SOFTLIMIT, 0);
	wbuf->delta = WBUF_TIMEOUT_HARDLIMIT - WBUF_TIMEOUT_SOFTLIMIT;
	wbuf->delta *= 1000000000ULL;
	ubifs_assert(wbuf->delta <= ULONG_MAX);
	return 0;
}
