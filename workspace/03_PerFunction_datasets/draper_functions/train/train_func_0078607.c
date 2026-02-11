cmd_ping_reply (SESSION * session)
{
	int ret;
        unsigned long pong = 0;

	if ((ret = packet_write (session, CMD_PONG, (void*)&pong, 4)) != 0) {
		DSFYDEBUG
			("packet_write(cmd=0x49) returned %d, aborting!\n",
			 ret);
	}

	return ret;
}
