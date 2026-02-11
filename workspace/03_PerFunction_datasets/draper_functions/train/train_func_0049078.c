sendto_msg(int sk, struct sockaddr *sa, socklen_t salen,
		unsigned char *msg, unsigned int len)
{
	int err;

	err = sendto(sk, msg, len, MSG_NOSIGNAL, sa, salen);
	if (err < 0) {
		err = -errno;
		LOG("sendto failed errno %d/%s", -err, strerror(-err));
	}

	g_assert_cmpint(err, >=, 0);
	if (err < 0)
		return err;

	return 0;
}
