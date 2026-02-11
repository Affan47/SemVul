minipc_server_get_fdset(struct minipc_ch *ch, fd_set *setptr)
{
	struct mpc_link *link = mpc_get_link(ch);

	CHECK_LINK(link);
	*setptr = link->fdset;
	return 0;
}
