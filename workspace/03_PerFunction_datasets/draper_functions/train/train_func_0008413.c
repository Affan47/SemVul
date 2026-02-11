ast_xml_doc_item_alloc(const char *name, const char *type)
{
	struct ast_xml_doc_item *item;

	if (!(item = ao2_alloc(sizeof(*item), ast_xml_doc_item_destructor))) {
		ast_log(AST_LOG_ERROR, "Failed to allocate memory for ast_xml_doc_item instance\n");
		return NULL;
	}

	if (   !(item->syntax = ast_str_create(128))
		|| !(item->seealso = ast_str_create(128))
		|| !(item->arguments = ast_str_create(128))
		|| !(item->synopsis = ast_str_create(128))
		|| !(item->description = ast_str_create(128))) {
		ast_log(AST_LOG_ERROR, "Failed to allocate strings for ast_xml_doc_item instance\n");
		goto ast_xml_doc_item_failure;
	}

	if (ast_string_field_init(item, 64)) {
		ast_log(AST_LOG_ERROR, "Failed to initialize string field for ast_xml_doc_item instance\n");
		goto ast_xml_doc_item_failure;
	}
	ast_string_field_set(item, name, name);
	ast_string_field_set(item, type, type);

	return item;

ast_xml_doc_item_failure:
	ao2_ref(item, -1);
	return NULL;
}
