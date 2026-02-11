handle_socket_abnorm(struct epoll_event *p_entry)
{
	g2_connection_t *w_entry = p_entry->data.ptr;
	const char *msg = NULL;

	if(p_entry->events & (uint32_t)EPOLLPRI)
		msg = "priority data (OOB) in connection";
	if(p_entry->events & (uint32_t)EPOLLERR)
		msg = "error in connection!";
	if(p_entry->events & (uint32_t)EPOLLHUP)
		msg = "HUP in connection";


	if(!msg)
		msg = "unknown problem";

	logg_posd(LOGF_DEVEL_OLD, "%s Ip: %p#I\tFDNum: %i\n",
	          msg, &w_entry->remote_host, w_entry->com_socket);


	return w_entry;
}
