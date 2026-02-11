ast_audiohook_detach_list(struct ast_audiohook_list *audiohook_list)
{
	int i = 0;
	struct ast_audiohook *audiohook = NULL;


	while ((audiohook = AST_LIST_REMOVE_HEAD(&audiohook_list->spy_list, list))) {
		ast_audiohook_update_status(audiohook, AST_AUDIOHOOK_STATUS_DONE);
	}


	while ((audiohook = AST_LIST_REMOVE_HEAD(&audiohook_list->whisper_list, list))) {
		ast_audiohook_update_status(audiohook, AST_AUDIOHOOK_STATUS_DONE);
	}


	while ((audiohook = AST_LIST_REMOVE_HEAD(&audiohook_list->manipulate_list, list))) {
		ast_audiohook_update_status(audiohook, AST_AUDIOHOOK_STATUS_DONE);
		audiohook->manipulate_callback(audiohook, NULL, NULL, 0);
	}


	for (i = 0; i < 2; i++) {
		if (audiohook_list->in_translate[i].trans_pvt)
			ast_translator_free_path(audiohook_list->in_translate[i].trans_pvt);
		if (audiohook_list->out_translate[i].trans_pvt)
			ast_translator_free_path(audiohook_list->out_translate[i].trans_pvt);
	}


	ast_free(audiohook_list);

	return 0;
}
