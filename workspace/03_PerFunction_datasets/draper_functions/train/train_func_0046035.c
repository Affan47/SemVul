del_socket(socket_queue **sock, int position)
{
	int Cnt;

	if (*sock == NULL)
		return -1;

	Cnt = socket_size((*sock));
	if (position < 0 || position >= Cnt)
		return -1;

	free((*sock)[position].msgbuf.buf);
	free((*sock)[position].restbuf.buf);
	free((*sock)[position].f_hostname);
	free((*sock)[position].f_username);

	if (position == 0 && Cnt == 1)
	{
		free(*sock);
		*sock = NULL;
		return 0;
	}

	close((*sock)[position].descriptor);
	memcpy(&((*sock)[position]),
		&((*sock)[Cnt-1]),
		sizeof(socket_queue));

 	memset(&((*sock)[Cnt-1]),0,sizeof(socket_queue));
 	(*sock)[Cnt-1].descriptor = NO_SOCKET;

 	(*sock) = (socket_queue*) realloc((*sock),sizeof(socket_queue)*Cnt);

	return (*sock)?0:NO_MEMORY;
}
