_dv_write_meta_data(unsigned char* target, int frame, int isPAL,
		     int is16x9, time_t * now)
{
	int numDIFseq;
	int ds;
	struct tm * now_t = NULL;

	numDIFseq = isPAL ? 12 : 10;

	if (frame % (isPAL ? 25 : 30) == 0) {
		(*now)++;
	}

	now_t = localtime(now);

	for (ds = 0; ds < numDIFseq; ds++) {
		write_header_block(target, ds, isPAL);
		target +=   1 * 80;
		write_subcode_blocks(target, ds, frame, now_t, isPAL);
		target +=   2 * 80;
		write_vaux_blocks(target, ds, now_t, isPAL, is16x9);
		target +=   3 * 80;
		write_video_headers(target, frame, ds);
		write_audio_headers(target, frame, ds);
		target += 144 * 80;
	}
}
