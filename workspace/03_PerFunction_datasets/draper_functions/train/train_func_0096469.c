replay_truncate(size_t len)
{
    int fd = open(filename_.c_str(), O_RDWR);
    if (fd < 0) {
	fprintf(stderr, "replay %s: %s\n", filename_.c_str(), strerror(errno));
	abort();
    }

    struct stat sb;
    int r = fstat(fd, &sb);
    if (r != 0) {
	fprintf(stderr, "replay %s: %s\n", filename_.c_str(), strerror(errno));
	abort();
    } else if (sb.st_size < off_t(len)) {
	fprintf(stderr, "replay %s: bad length %" PRIdOFF_T "\n", filename_.c_str(), sb.st_size);
	abort();
    }

    r = ftruncate(fd, len);
    if (r != 0) {
	fprintf(stderr, "replay %s: truncate: %s\n", filename_.c_str(), strerror(errno));
	abort();
    }

    off_t off = lseek(fd, len, SEEK_SET);
    if (off == (off_t) -1) {
	fprintf(stderr, "replay %s: seek: %s\n", filename_.c_str(), strerror(errno));
	abort();
    }

    return fd;
}
