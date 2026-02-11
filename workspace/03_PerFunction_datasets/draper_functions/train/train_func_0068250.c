comp_zlib_uncompress(char *outbuf, unsigned int *outlen, char *source, unsigned int sourcelen) {
	int r;
	uLongf t_outlen = *outlen;
	r = uncompress(outbuf, &t_outlen, source, sourcelen);
	*outlen = t_outlen;
	if(r == Z_OK) return COMP_OK;
	if(r == Z_BUF_ERROR) return COMP_SIZERR;
	if(r == Z_DATA_ERROR) return COMP_DATAERR;
	return COMP_MISCERR;
}
