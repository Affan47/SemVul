watch_file(int kq, WatchFile *file) {
	struct kevent evSet;
	int i;
	struct timespec delay = { 0, 100 * MILLISECOND };


	for (i=0; i < 10; i++) {
		#ifdef O_EVTONLY
		file->fd = _open(file->fn, O_RDONLY|O_EVTONLY);
		#else
		file->fd = _open(file->fn, O_RDONLY);
		#endif
		if (file->fd == -1) nanosleep(&delay, NULL);
		else break;
	}
	if (file->fd == -1)
		err(errno, "cannot open `%s'", file->fn);

	EV_SET(&evSet, file->fd, EVFILT_VNODE, EV_ADD | EV_CLEAR, NOTE_ALL, 0,
	    file);
	if (_kevent(kq, &evSet, 1, NULL, 0, NULL) == -1)
		err(1, "failed to register VNODE event");
}
