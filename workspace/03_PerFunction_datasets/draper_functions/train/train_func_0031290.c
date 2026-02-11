message_parse_binary_file(FILE *infile, struct body **body)
{
    int fd = fileno(infile);
    struct stat sbuf;
    struct msg msg;
    size_t n;

    if (fstat(fd, &sbuf) == -1) {
	syslog(LOG_ERR, "IOERROR: fstat on new message in spool: %m");
	fatal("can't fstat message file", EC_OSFILE);
    }
    msg.len = sbuf.st_size;
    msg.base = xmalloc(msg.len);
    msg.offset = 0;
    msg.encode = 1;

    lseek(fd, 0L, SEEK_SET);

    n = retry_read(fd, (char*) msg.base, msg.len);
    if (n != msg.len) {
	syslog(LOG_ERR, "IOERROR: reading binary file in spool: %m");
	return IMAP_IOERROR;
    }

    if (!*body) *body = (struct body *) xmalloc(sizeof(struct body));
    message_parse_body(&msg, *body,
		       DEFAULT_CONTENT_TYPE, (struct boundary *)0);

    message_guid_generate(&(*body)->guid, msg.base, msg.len);

    lseek(fd, 0L, SEEK_SET);
    n = retry_write(fd, msg.base, msg.len);

    free((char*) msg.base);

    if (n != msg.len || fsync(fd)) {
	syslog(LOG_ERR, "IOERROR: rewriting binary file in spool: %m");
	return IMAP_IOERROR;
    }

    return 0;
}
