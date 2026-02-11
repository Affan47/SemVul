wav_read(struct ast_filestream *s, int *whennext)
{

	struct wavg_desc *fs = (struct wavg_desc *)s->_private;

	s->fr.frametype = AST_FRAME_VOICE;
	ast_format_set(&s->fr.subclass.format, AST_FORMAT_GSM, 0);
	s->fr.offset = AST_FRIENDLY_OFFSET;
	s->fr.samples = GSM_SAMPLES;
	s->fr.mallocd = 0;
	AST_FRAME_SET_BUFFER(&s->fr, s->buf, AST_FRIENDLY_OFFSET, GSM_FRAME_SIZE);
	if (fs->secondhalf) {

		s->fr.data.ptr = (char *)s->fr.data.ptr + GSM_FRAME_SIZE;
		s->fr.offset += GSM_FRAME_SIZE;
	} else {

		unsigned char msdata[MSGSM_FRAME_SIZE];
		int res;

		if ((res = fread(msdata, 1, MSGSM_FRAME_SIZE, s->f)) != MSGSM_FRAME_SIZE) {
			if (res && (res != 1))
				ast_log(LOG_WARNING, "Short read (%d) (%s)!\n", res, strerror(errno));
			return NULL;
		}

		conv65(msdata, s->fr.data.ptr);
	}
	fs->secondhalf = !fs->secondhalf;
	*whennext = GSM_SAMPLES;
	return &s->fr;
}
