pcm_codec_process(int type, codec_way_t way, string_t input, string_t output, void *data) {
	pcm_private_t *c = data;
	int inchunklen = (c->ibps / 8) * c->ich;
	int outchunklen = (c->obps / 8) * c->och;

	int inchunks = input->len / inchunklen;
	int outchunks = (int) ((double) c->ofreq / (double) c->ifreq * (double) inchunks);
	int i;
	char *out;


	if (type) return 0;
	if (!input || !output) return -1;

	debug("pcm_codec_process() inchunks: %d inchunklen: %d outchunks: %d outchunklen: %d\n", inchunks, inchunklen, outchunks, outchunklen);

	out = xmalloc(outchunklen);
	for (i = 0; i < outchunks; i++) {
		int j = (int) ((double) i / (double) outchunks * (double) inchunks);

		pcm_recode(input->str + j * inchunklen, c->ibps, c->ich, out, c->obps, c->och);
		string_append_raw(output, out, outchunklen);
	}
	xfree(out);
	return (inchunks * inchunklen);
}
