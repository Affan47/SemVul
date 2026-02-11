eio_handle_mainloop(eio_handle_t *eio)
{
	int            retval  = 0;
	struct pollfd *pollfds = NULL;
	eio_obj_t    **map     = NULL;
	unsigned int   maxnfds = 0, nfds = 0;
	unsigned int   n       = 0;

	xassert (eio != NULL);
	xassert (eio->magic == EIO_MAGIC);

	for (;;) {


		n = list_count(eio->obj_list);
		if (maxnfds < n) {
			maxnfds = n;
			xrealloc(pollfds, (maxnfds+1) * sizeof(struct pollfd));
			xrealloc(map,     maxnfds     * sizeof(eio_obj_t *  ));


		}

		debug4("eio: handling events for %d objects",
		       list_count(eio->obj_list));
		nfds = _poll_setup_pollfds(pollfds, map, eio->obj_list);
		if ((nfds <= 0) ||
		    (pollfds == NULL))
			goto done;


		pollfds[nfds].fd     = eio->fds[0];
		pollfds[nfds].events = POLLIN;
		nfds++;

		xassert(nfds <= maxnfds + 1);

		if (_poll_internal(pollfds, nfds) < 0)
			goto error;

		if (pollfds[nfds-1].revents & POLLIN)
			_eio_wakeup_handler(eio);

		_poll_dispatch(pollfds, nfds-1, map, eio->obj_list);

		if (eio_shutdown_time &&
		    (difftime(time(NULL), eio_shutdown_time) >=
		     EIO_SHUTDOWN_WAIT)) {
			error("Abandoning IO %d secs after job shutdown "
			      "initiated", EIO_SHUTDOWN_WAIT);
			break;
		}
	}
  error:
	retval = -1;
  done:
	xfree(pollfds);
	xfree(map);
	return retval;
}
