gsm_write(struct ast_filestream *fs, struct ast_frame *f)
{
	int res;
	unsigned char gsm[2*GSM_FRAME_SIZE];

	if (f->frametype != AST_FRAME_VOICE) {
		ast_log(LOG_WARNING, "Asked to write non-voice frame!\n");
		return -1;
	}
	if (f->subclass.format.id != AST_FORMAT_GSM) {
		ast_log(LOG_WARNING, "Asked to write non-GSM frame (%s)!\n", ast_getformatname(&f->subclass.format));
		return -1;
	}
	if (!(f->datalen % 65)) {

		int len=0;
		while(len < f->datalen) {
			conv65(f->data.ptr + len, gsm);
			if ((res = fwrite(gsm, 1, 2*GSM_FRAME_SIZE, fs->f)) != 2*GSM_FRAME_SIZE) {
				ast_log(LOG_WARNING, "Bad write (%d/66): %s\n", res, strerror(errno));
				return -1;
			}
			len += 65;
		}
	} else {
		if (f->datalen % GSM_FRAME_SIZE) {
			ast_log(LOG_WARNING, "Invalid data length, %d, should be multiple of 33\n", f->datalen);
			return -1;
		}
		if ((res = fwrite(f->data.ptr, 1, f->datalen, fs->f)) != f->datalen) {
				ast_log(LOG_WARNING, "Bad write (%d/33): %s\n", res, strerror(errno));
				return -1;
		}
	}
	return 0;
}
