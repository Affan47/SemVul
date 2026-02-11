save_all(void)
{
	struct text *text;
	Boolean_t msg = FALSE;
	char *raw;

	for (text = text_list; text; text = text->next) {
		if (!text->path || !text->buffer || !text->buffer->path)
			continue;
		text_unfold_all(text);
		if (text->clean &&
		    buffer_raw(text->buffer, &raw, 0, ~0) ==
			text->clean_bytes &&
		    !memcmp(text->clean, raw, text->clean_bytes)) {
			unlink(text->buffer->path);
			continue;
		}
		if (!msg) {
			fprintf(stderr, "\ncheck working files for "
				"current unsaved data\n");
			msg = TRUE;
		}
		fprintf(stderr, "\t%s\n", text->buffer->path);
		buffer_snap(text->buffer);
	}
}
