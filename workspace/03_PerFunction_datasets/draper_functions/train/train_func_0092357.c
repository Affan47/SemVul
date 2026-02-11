init()
{
	if (initialized)
	{
		return 1;
	}

	if (SDLNet_Init() == -1)
	{
		ERR("Unable to init SDLNet: %s\n", SDLNet_GetError());
		return 0;
	}

	for (int i = 0; i < MAX_UDP_SOCKETS; i++)
	{
		udp_socket_list[i] = NULL;
	}

	initialized = 1;

	return 1;
}
