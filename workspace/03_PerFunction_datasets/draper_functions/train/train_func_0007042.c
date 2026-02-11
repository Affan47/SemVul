mqc_byteout(opj_mqc_t *mqc) {
	if (*mqc->bp == 0xff) {
		mqc->bp++;
		*mqc->bp = mqc->c >> 20;
		mqc->c &= 0xfffff;
		mqc->ct = 7;
	} else {
		if ((mqc->c & 0x8000000) == 0) {
			mqc->bp++;
			*mqc->bp = mqc->c >> 19;
			mqc->c &= 0x7ffff;
			mqc->ct = 8;
		} else {
			(*mqc->bp)++;
			if (*mqc->bp == 0xff) {
				mqc->c &= 0x7ffffff;
				mqc->bp++;
				*mqc->bp = mqc->c >> 20;
				mqc->c &= 0xfffff;
				mqc->ct = 7;
			} else {
				mqc->bp++;
				*mqc->bp = mqc->c >> 19;
				mqc->c &= 0x7ffff;
				mqc->ct = 8;
			}
		}
	}
}
