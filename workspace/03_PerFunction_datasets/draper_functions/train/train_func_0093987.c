link_accept(struct link *master, time_t stoptime)
{
	struct link *link = 0;

	if(master->type == LINK_TYPE_FILE) {
		return NULL;
	}

	link = link_create();
	if(!link)
		goto failure;

	while(1) {
		if(!link_sleep(master, stoptime, 1, 0))
			goto failure;
		link->fd = accept(master->fd, 0, 0);
		break;
	}

	if(!link_nonblocking(link, 1))
		goto failure;
	if(!link_address_remote(link, link->raddr, &link->rport))
		goto failure;
	link_squelch();

	debug(D_TCP, "got connection from %s:%d", link->raddr, link->rport);

	return link;

      failure:
	if(link)
		link_close(link);
	return 0;
}
