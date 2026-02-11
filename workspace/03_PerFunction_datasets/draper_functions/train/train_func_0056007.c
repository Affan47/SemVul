cooked1394_read(raw1394handle_t handle, nodeid_t node, nodeaddr_t addr,
                    size_t length, quadlet_t *buffer)
{
	int retval, i;
	struct timespec ts = {0, RETRY_DELAY};
	for(i=0; i<MAXTRIES; i++) {
		retval = raw1394_read(handle, node, addr, length, buffer);
		if (retval < 0 && errno == EAGAIN)
			nanosleep(&ts, NULL);
		else
			return retval;
	}
	return -1;
}
