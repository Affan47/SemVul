do_rd(int fd, void **paramp)
{
	identd_buf_t *buf = *paramp;
	char *cur, *p;
	int retval = 0;
	int sz;

	cur = buf->buf + buf->pos;

	if (buf->fd_flag & O_NONBLOCK)
		fcntl(fd, F_SETFL, buf->fd_flag);
	sz = safe_read(fd, cur, sizeof(buf->buf) - buf->pos);

	if (sz < 0) {
		if (errno != EAGAIN)
			goto term;
		goto ok;
	}

	buf->pos += sz;
	buf->buf[buf->pos] = '\0';
	p = strpbrk(cur, "\r\n");
	if (p)
		*p = '\0';
	if (!p && sz && buf->pos <= (int)sizeof(buf->buf))
		goto ok;


	if (fd == 0) fd++;
	fdprintf(fd, "%s : USERID : UNIX : %s\r\n", buf->buf, bogouser);
 term:
	free(buf);
	retval = 1;
 ok:
	if (buf->fd_flag & O_NONBLOCK)
		fcntl(fd, F_SETFL, buf->fd_flag & ~O_NONBLOCK);
	return retval;
}
