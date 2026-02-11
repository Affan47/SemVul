release_page_wait_timeout(struct fscache_cookie *cookie, struct page *page)
{
	wait_queue_head_t *wq = bit_waitqueue(&cookie->flags, 0);

	return wait_event_timeout(*wq, !__fscache_check_page_write(cookie, page),
				  HZ);
}
