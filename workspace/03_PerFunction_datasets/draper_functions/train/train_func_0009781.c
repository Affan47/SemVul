j2k_read_plt(opj_j2k_t *j2k) {
	int len, i, Zplt, packet_len = 0, add;

	opj_cio_t *cio = j2k->cio;

	len = cio_read(cio, 2);
	Zplt = cio_read(cio, 1);
	for (i = len - 3; i > 0; i--) {
		add = cio_read(cio, 1);
		packet_len = (packet_len << 7) + add;
		if ((add & 0x80) == 0) {

			packet_len = 0;
		}
	}
}
