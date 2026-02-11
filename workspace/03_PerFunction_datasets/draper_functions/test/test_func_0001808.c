huawei_send(const char *cmd)
{
    int len, bytes;
    char buf[SEND_BUFFER_SIZE];

    sprintf(buf, "%s\r", cmd);
    len = strlen(buf);


    bytes = write(fd, buf, len);


    if (bytes > 0)
	buf[bytes] = '\0';
    else
	buf[0] = '\0';

    if (bytes < 0 && errno != EAGAIN) {
	error("%s: ERROR: Writing to device %s failed: %s", name, port, strerror(errno));
	return -1;
    } else if (bytes != len) {
	error("%s: ERROR: Partial write when writing to device %s", name, port);
	return -1;
    }


    while (bytes > 0 && buf[bytes - 1] == '\r') {
	buf[--bytes] = '\0';
    }

    if (debug)
	debug("DEBUG: <-Send bytes=%i, send buf=%s", bytes, buf);

    return bytes;
}
