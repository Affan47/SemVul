savemetawrite(struct metafd *mfd, const void *buf, size_t nbyte)
{
	ssize_t ret;
	int gzerr;
	const char *gzerrmsg;

	if (mfd->gziplevel == 0) {
		return write(mfd->fd, buf, nbyte);
	}

	ret = gzwrite(mfd->gzfd, buf, nbyte);
	if (ret != nbyte) {
		gzerrmsg = gzerror(mfd->gzfd, &gzerr);
		if (gzerr != Z_ERRNO) {
			fprintf(stderr, "Error: zlib: %s\n", gzerrmsg);
		}
	}
	return ret;
}
