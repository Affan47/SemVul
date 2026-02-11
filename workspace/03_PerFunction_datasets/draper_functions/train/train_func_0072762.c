mqc_flush(opj_mqc_t *mqc) {
	mqc_setbits(mqc);
	mqc->c <<= mqc->ct;
	mqc_byteout(mqc);
	mqc->c <<= mqc->ct;
	mqc_byteout(mqc);

	if (*mqc->bp != 0xff) {
		mqc->bp++;
	}
}
