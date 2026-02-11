ast_slinfactory_destroy(struct ast_slinfactory *sf)
{
	struct ast_frame *f;

	if (sf->trans) {
		ast_translator_free_path(sf->trans);
		sf->trans = NULL;
	}

	while ((f = AST_LIST_REMOVE_HEAD(&sf->queue, frame_list)))
		ast_frfree(f);
}
