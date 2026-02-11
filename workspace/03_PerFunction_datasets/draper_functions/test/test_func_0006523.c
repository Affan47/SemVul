get(Input *in) {
	int c;
	while ((c = (in->buf < in->bufend ? *in->buf++ : (*in->fill)(in))) == '\0')
		warn("null character ignored");
	return c;
}
