cmd_read(Filerange *range, enum CmdOpt opt, const char *argv[]) {
	size_t pos = window_cursor_get(vis->win->win);
	for (const char **file = &argv[1]; *file; file++) {
		int fd = open(*file, O_RDONLY);
		char *data = NULL;
		struct stat info;
		if (fd == -1)
			goto err;
		if (fstat(fd, &info) == -1)
			goto err;
		if (!S_ISREG(info.st_mode))
			goto err;

		data = mmap(NULL, info.st_size, PROT_READ, MAP_SHARED, fd, 0);
		if (data == MAP_FAILED)
			goto err;

		text_insert(vis->win->text->data, pos, data, info.st_size);
		pos += info.st_size;
	err:
		if (fd != -1)
			close(fd);
		if (data && data != MAP_FAILED)
			munmap(data, info.st_size);
	}
	editor_draw(vis);
	return true;
}
