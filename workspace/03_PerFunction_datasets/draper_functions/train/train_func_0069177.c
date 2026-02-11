audiohook_inheritance_destroy(void *data)
{
	struct audiohook_inheritance_datastore *audiohook_inheritance_datastore = data;
	struct inheritable_audiohook *inheritable_audiohook = NULL;

	while ((inheritable_audiohook = AST_LIST_REMOVE_HEAD(&audiohook_inheritance_datastore->allowed_list, list))) {
		ast_free(inheritable_audiohook);
	}

	ast_free(audiohook_inheritance_datastore);
}
