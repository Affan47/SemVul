write_data(int fd, struct shell_buf *sb)
{
	if (!sb) {
		return -1;
	}
	sb->wrote = 0;
	if (sb->fill > 0 && sb->writable) {
		ssize_t ret;

		ret = unix_write(fd, &sb->buf[sb->pos], sb->fill);
		switch (ret) {
		case 0:
			sb->hup = 1;
			break;
		case -1:
			if (EPIPE == errno) {
				sb->hup = 1;
			}
			if (!is_temporary_error(errno)) {
				if (sb->server) {
					perror("write() to server failed");
				} else if (!sb->hup) {
					perror("write() failed");
				}
				return -1;
			}
			break;
		default:
			sb->fill -= (size_t) ret;
			if (sb->fill > 0) {
				sb->pos += (size_t) ret;
			} else {
				sb->pos = 0;
			}
			sb->wrote = 1;
		}
	}
	return 0;
}
