connect_unix(struct path_ctx *s)
{
    struct sockaddr_un addr;

    addr.sun_family = AF_UNIX;
    strlcpy(addr.sun_path, s->path, sizeof(addr.sun_path));

    s->fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (s->fd < 0)
	return errno;
    rk_cloexec(s->fd);

    if (connect(s->fd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
	close(s->fd);
	return errno;
    }

    return 0;
}
