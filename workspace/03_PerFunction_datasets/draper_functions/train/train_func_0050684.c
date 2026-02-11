text_load(const char *filename) {
	Text *txt = calloc(1, sizeof(Text));
	if (!txt)
		return NULL;
	txt->fd = -1;
	txt->begin.index = 1;
	txt->end.index = 2;
	txt->piece_count = 2;
	piece_init(&txt->begin, NULL, &txt->end, NULL, 0);
	piece_init(&txt->end, &txt->begin, NULL, NULL, 0);
	lineno_cache_invalidate(&txt->lines);
	if (filename) {
		text_filename_set(txt, filename);
		txt->fd = open(filename, O_RDONLY);
		if (txt->fd == -1)
			goto out;
		if (fstat(txt->fd, &txt->info) == -1)
			goto out;
		if (!S_ISREG(txt->info.st_mode)) {
			errno = S_ISDIR(txt->info.st_mode) ? EISDIR : ENOTSUP;
			goto out;
		}

		txt->buf.size = txt->info.st_size;
		if (txt->buf.size != 0) {
			txt->buf.data = mmap(NULL, txt->info.st_size, PROT_READ, MAP_SHARED, txt->fd, 0);
			if (txt->buf.data == MAP_FAILED)
				goto out;
		}

		Piece *p = piece_alloc(txt);
		if (!p)
			goto out;
		piece_init(&txt->begin, NULL, p, NULL, 0);
		piece_init(p, &txt->begin, &txt->end, txt->buf.data, txt->buf.size);
		piece_init(&txt->end, p, NULL, NULL, 0);
		txt->size = txt->buf.size;
	}
	return txt;
out:
	if (txt->fd > 2) {
		close(txt->fd);
		txt->fd = -1;
	}
	text_free(txt);
	return NULL;
}
