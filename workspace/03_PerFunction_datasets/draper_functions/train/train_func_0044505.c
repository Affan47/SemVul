IoSocket_asyncUdpOpen(IoSocket *self, IoObject *locals, IoMessage *m)
{


	Socket *socket = SOCKET(self);

	if (Socket_udpOpen(socket) && Socket_isOpen(socket) && Socket_makeReusable(socket) && Socket_makeAsync(socket))
	{
		IoSocket_rawSetupEvents(self, locals, m);
		return self;
	}
	else
	{
		return SOCKETERROR("Failed to create udp socket");
	}
}
