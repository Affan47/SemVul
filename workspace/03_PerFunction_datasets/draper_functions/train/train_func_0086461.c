inflate_write_output(unsigned char *buf, unsigned int len) {
	if ((o_ix + len) > o_len) {
		fprintf(stderr,"Uncompressed buffer is unexpectedly large (%ld > %ld)!\n", o_ix + len, o_len);
		return 1;
	}
	memmove(o_buf + o_ix, buf, len);
	o_ix += len;
	return 0;
}
