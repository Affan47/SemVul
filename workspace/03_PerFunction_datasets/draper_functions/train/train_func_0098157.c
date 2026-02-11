fuse_send_msg(struct fuse_ll *f, struct fuse_chan *ch,
			 struct iovec *iov, int count)
{
	struct fuse_out_header *out = iov[0].iov_base;

	out->len = iov_length(iov, count);
	if (f->debug) {
		if (out->unique == 0) {
			fprintf(stderr, "NOTIFY: code=%d length=%u\n",
				out->error, out->len);
		} else if (out->error) {
			fprintf(stderr,
				"   unique: %llu, error: %i (%s), outsize: %i\n",
				(unsigned long long) out->unique, out->error,
				strerror(-out->error), out->len);
		} else {
			fprintf(stderr,
				"   unique: %llu, success, outsize: %i\n",
				(unsigned long long) out->unique, out->len);
		}
	}

	return fuse_chan_send(ch, iov, count);
}
