__frame_free(struct ast_frame *fr, int cache)
{
	if (!fr->mallocd)
		return;

#if !defined(LOW_MEMORY)
	if (cache && fr->mallocd == AST_MALLOCD_HDR) {


		struct ast_frame_cache *frames;

		if ((frames = ast_threadstorage_get(&frame_cache, sizeof(*frames))) &&
		    (frames->size < FRAME_CACHE_MAX_SIZE)) {
			AST_LIST_INSERT_HEAD(&frames->list, fr, frame_list);
			frames->size++;
			return;
		}
	}
#endif

	if (fr->mallocd & AST_MALLOCD_DATA) {
		if (fr->data.ptr)
			ast_free(fr->data.ptr - fr->offset);
	}
	if (fr->mallocd & AST_MALLOCD_SRC) {
		if (fr->src)
			ast_free((void *) fr->src);
	}
	if (fr->mallocd & AST_MALLOCD_HDR) {
		ast_free(fr);
	}
}
