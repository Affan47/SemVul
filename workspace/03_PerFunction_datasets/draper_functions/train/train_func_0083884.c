huawei_receive(void)
{
    int run, count, bytes;
    char c[1], *p;
    static char buf[RECV_BUFFER_SIZE];


    for (run = 0; run < 4; run++) {


	p = buf;


	count = RECV_BUFFER_SIZE;


	while (count > 1) {
	    bytes = read(fd, c, 1);

	    if (*c == '\n' || *c == '\r' || (bytes < 0 && errno != EAGAIN))
		break;

	    *p = *c;
	    p++;
	    count--;
	}


	*p = '\0';


	if (strlen(buf) > 0 || (bytes < 0 && errno != EAGAIN))
	    break;
    }

    if (bytes < 0 && errno != EAGAIN) {
	error("%s: ERROR: Reading from device %s failed: %s", name, port, strerror(errno));
	return ("");
    }


    if (debug)
	debug("DEBUG: ->Received bytes=%i, receive buf=%s", (int) strlen(buf), buf);

    return (buf);
}
