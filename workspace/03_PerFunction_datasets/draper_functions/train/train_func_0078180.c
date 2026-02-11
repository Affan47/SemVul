ipc_tick(struct ipc_softc *sc)
{
	char c;
	ssize_t l;

	c = MESSAGE_TICK;
	l = send(sc->socket, &c, 1, 0);
	if(l != 1)
		return 0;
	return 1;
}
