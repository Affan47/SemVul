rb_fdlist_init(int closeall, int maxfds, size_t heapsize)
{
	static int initialized = 0;
#ifdef _WIN32
	WSADATA wsaData;
	int err;
	int vers = MAKEWORD(2, 0);

	err = WSAStartup(vers, &wsaData);
	if(err != 0)
	{
		rb_lib_die("WSAStartup failed");
	}

#endif
	if(!initialized)
	{
		rb_maxconnections = maxfds;
		if(closeall)
			rb_close_all();

		initialized = 1;
	}
	fd_heap = rb_bh_create(sizeof(rb_fde_t), heapsize, "librb_fd_heap");

}
