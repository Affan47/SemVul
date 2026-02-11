bio_getbit(opj_bio_t *bio) {
	if (bio->ct == 0) {
		bio_bytein(bio);
	}
	bio->ct--;
	return (bio->buf >> bio->ct) & 1;
}
