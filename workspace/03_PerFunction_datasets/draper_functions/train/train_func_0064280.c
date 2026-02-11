package_read_do (xmmsc_visualization_t *v, short *buffer, int drawtime, unsigned int blocking)
{
	if (v->type == VIS_UNIXSHM) {
		return read_do_shm (&v->transport.shm, v, buffer, drawtime, blocking);
	} else if (v->type == VIS_UDP) {
		return read_do_udp (&v->transport.udp, v, buffer, drawtime, blocking);
	}

	return -1;
}
