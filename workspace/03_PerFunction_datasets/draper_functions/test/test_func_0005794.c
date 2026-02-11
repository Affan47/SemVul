g729_write(struct ast_filestream *fs, struct ast_frame *f)
{
	int res;
	if (f->frametype != AST_FRAME_VOICE) {
		ast_log(LOG_WARNING, "Asked to write non-voice frame!\n");
		return -1;
	}
	if (f->subclass.format.id != AST_FORMAT_G729A) {
		ast_log(LOG_WARNING, "Asked to write non-G729 frame (%s)!\n", ast_getformatname(&f->subclass.format));
		return -1;
	}
	if (f->datalen % 10) {
		ast_log(LOG_WARNING, "Invalid data length, %d, should be multiple of 10\n", f->datalen);
		return -1;
	}
	if ((res = fwrite(f->data.ptr, 1, f->datalen, fs->f)) != f->datalen) {
			ast_log(LOG_WARNING, "Bad write (%d/10): %s\n", res, strerror(errno));
			return -1;
	}
	return 0;
}
