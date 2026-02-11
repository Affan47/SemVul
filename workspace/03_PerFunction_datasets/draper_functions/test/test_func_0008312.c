WriteBytes() {
	if (write_buf == NULL)
		return 0;

    uint8_t dptr[1024];
    int dlen, ret;

    write_buf->FetchPtr(dptr, 1024, &dlen);

    if ((ret = write(ipipe[1], dptr, dlen)) <= 0) {
        snprintf(errstr, 1024, "Popen client: Killing client write error %s",
                 strerror(errno));
        globalreg->messagebus->InjectMessage(errstr, MSGFLAG_ERROR);
		KillConnection();
        return -1;
    }

    write_buf->MarkRead(ret);

    return ret;
}
