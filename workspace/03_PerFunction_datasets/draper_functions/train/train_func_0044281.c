readFromSocketn(char *buff, int len, unsigned int flags, int timeout)
{
	int cnt, rc;
	cnt = len;


	if ((bufflen - buffstart) > 0) {


		int tocopy = len;
		if ((bufflen - buffstart) < len)
			tocopy = bufflen - buffstart;
		memcpy(buff, buffer + buffstart, tocopy);
		cnt -= tocopy;
		buffstart += tocopy;
		buff += tocopy;
		if (cnt == 0)
			return len;
	}

	while (cnt > 0) {
		try {
			checkForInput(timeout);
		}
		catch(std::exception & e) {
			return -1;
		}
		rc = recv(sck, buff, cnt, flags);
		if (rc < 0) {
			if (errno == EINTR) {
				continue;
			}
			return -1;
		}
		if (rc == 0) {
			return len - cnt;
		}
		buff += rc;
		cnt -= rc;
	}
	return len;
}
