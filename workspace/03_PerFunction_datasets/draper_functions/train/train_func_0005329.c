pollAdd(int fd)
{

	struct pollfd  *tmp_poll_list;

	m_lock(&gLock);

	if(poll_len == poll_len_inuse) {
		tmp_poll_list = (struct pollfd  *)realloc(poll_list, sizeof(struct pollfd) * (poll_len_inuse + 1));
		if (tmp_poll_list == NULL) {
			m_unlock(&gLock);
			return -1;
		}
		++poll_len_inuse;
		poll_list = tmp_poll_list;
	}

	poll_list[poll_len].fd = fd;
	poll_list[poll_len].events = POLLIN ;


	poll_list[0].events = POLLIN;

	++poll_len;
	m_unlock(&gLock);
	return 0;
}
