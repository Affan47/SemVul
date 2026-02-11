frame_cache_cleanup(void *data)
{
	struct ast_frame_cache *frames = data;
	struct ast_frame *f;

	while ((f = AST_LIST_REMOVE_HEAD(&frames->list, frame_list)))
		ast_free(f);

	ast_free(frames);
}
