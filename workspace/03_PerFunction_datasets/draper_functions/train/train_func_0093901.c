opj_bio_read(opj_bio_t *bio, OPJ_UINT32 n) {
	OPJ_INT32 i;
    OPJ_UINT32 v;
	v = 0;
	for (i = n - 1; i >= 0; i--) {
		v += opj_bio_getbit(bio) << i;
	}
	return v;
}
