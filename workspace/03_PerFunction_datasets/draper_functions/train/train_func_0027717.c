fdevent_unregister(fdevents *ev, int fd) {
	fdnode *fdn;
        if (!ev) return 0;
	fdn = ev->fdarray[fd];

	fdnode_free(fdn);

	ev->fdarray[fd] = NULL;

	return 0;
}
