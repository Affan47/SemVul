rb_thread_fd_select(int max, rb_fdset_t * read, rb_fdset_t * write, rb_fdset_t * except,
		    struct timeval *timeout)
{
    if (!read && !write && !except) {
	if (!timeout) {
	    rb_thread_sleep_forever();
	    return 0;
	}
	rb_thread_wait_for(*timeout);
	return 0;
    }

    if (read) {
	rb_fd_resize(max - 1, read);
    }
    if (write) {
	rb_fd_resize(max - 1, write);
    }
    if (except) {
	rb_fd_resize(max - 1, except);
    }
    return do_select(max, read, write, except, timeout);
}
