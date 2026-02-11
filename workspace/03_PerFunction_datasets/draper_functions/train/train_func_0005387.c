create_udp_socket(int family)
{
	int sk, err;

	sk = socket(family, SOCK_DGRAM, IPPROTO_UDP);
	if (sk < 0) {
		err = errno;
		LOG("Failed to create UDP socket %d/%s", err, strerror(err));
		return -err;
	}

	return sk;
}
