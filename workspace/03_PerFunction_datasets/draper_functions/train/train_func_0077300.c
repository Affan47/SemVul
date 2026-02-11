text_close(struct text *text)
{
	struct text *prev = NULL, *bp;

	for (bp = text_list; bp; prev = bp, bp = bp->next)
		if (bp == text) {
			if (prev)
				prev->next = text->next;
			else
				text_list = text->next;
			break;
		}

	if (text->clean)
		munmap(text->clean, text->clean_bytes);
	buffer_destroy(text->buffer);
	text_forget_undo(text);
	if (text->fd >= 0)
		close(text->fd);
	if (text->flags & (TEXT_SCRATCH | TEXT_CREATED))
		unlink(text->path);
	RELEASE(text->path);
	RELEASE(text);
}
