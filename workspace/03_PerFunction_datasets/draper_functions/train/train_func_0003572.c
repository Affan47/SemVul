text_dirty(struct text *text)
{
	if (text->path && !text->dirties && text->flags & TEXT_RDONLY)
		message("%s: read-only, %s",
			path_format(text->path),
			make_writable ? "will be made writable"
				      : "changes won't be saved here");
	text->dirties++;
	if (!text->buffer) {
		text->buffer = buffer_create(text->fd >= 0 ? text->path : NULL);
		if (text->clean)
			buffer_insert(text->buffer, text->clean, 0,
				      text->clean_bytes);
		grab_mtime(text);
	}
}
