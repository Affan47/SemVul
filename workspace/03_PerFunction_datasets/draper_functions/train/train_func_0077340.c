ast_xml_doc_item_hash(const void *obj, const int flags)
{
	const struct ast_xml_doc_item *item = obj;
	const char *name = (flags & OBJ_KEY) ? obj : item->name;
	return ast_str_case_hash(name);
}
