filerProcessStream(filerFileStruct_t *f, uint8_t final) {
	uint32_t res;
	UINT bytes = 0;
	uint32_t size;

	if (!f->open) {
		sprintf(filerData.buf, "%03d-%s.LOG", (int)filerData.session, f->fileName);
		res = f_open(&f->fp, filerData.buf, FA_CREATE_ALWAYS | FA_WRITE);
		if (res != FR_OK) {
			return -1;
		}

		f->open = 1;
	}


	while (f->tail > f->head || (f->head - f->tail) >= f->length/FILER_FLUSH_THRESHOLD || ((f->length <= 512 || final) && f->head != f->tail)) {
		if (f->head > f->tail) {
			size = f->head - f->tail;
		} else {
			size = f->length - f->tail;
		}

		res = f_write(&f->fp, f->buf + f->tail, size, &bytes);
		f->tail = (f->tail + bytes) % f->length;

		if (res != FR_OK) {
			return -1;
		}
	}

	return bytes;
}
