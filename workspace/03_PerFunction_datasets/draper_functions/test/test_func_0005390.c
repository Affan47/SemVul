ast_format_cap_add_all_by_type(struct ast_format_cap *cap, enum ast_format_type type)
{
	int x;
	size_t f_len = 0;
	const struct ast_format_list *f_list = ast_format_list_get(&f_len);

	for (x = 0; x < f_len; x++) {
		if (AST_FORMAT_GET_TYPE(f_list[x].format.id) == type) {
			ast_format_cap_add(cap, &f_list[x].format);
		}
	}
	ast_format_list_destroy(f_list);
}
