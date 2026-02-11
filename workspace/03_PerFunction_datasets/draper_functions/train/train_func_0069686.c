ctf_declaration_struct_visit(FILE *fd,
	int depth, const char *name, struct bt_list_head *declaration_list,
	int has_body, struct bt_list_head *min_align,
	struct declaration_scope *declaration_scope,
	struct ctf_trace *trace)
{
	struct declaration_struct *struct_declaration;
	struct ctf_node *iter;


	if (!has_body) {
		if (!name)
			return NULL;
		struct_declaration =
			bt_lookup_struct_declaration(g_quark_from_string(name),
						  declaration_scope);
		bt_declaration_ref(&struct_declaration->p);
		return &struct_declaration->p;
	} else {
		uint64_t min_align_value = 0;


		if (name) {
			if (bt_lookup_struct_declaration(g_quark_from_string(name),
						      declaration_scope)) {
				fprintf(fd, "[error] %s: struct %s already declared in scope\n", __func__, name);
				return NULL;
			}
		}
		if (!bt_list_empty(min_align)) {
			int ret;

			ret = get_unary_unsigned(min_align, &min_align_value);
			if (ret) {
				fprintf(fd, "[error] %s: unexpected unary expression for structure \"align\" attribute\n", __func__);
				goto error;
			}
		}
		struct_declaration = bt_struct_declaration_new(declaration_scope,
							    min_align_value);
		bt_list_for_each_entry(iter, declaration_list, siblings) {
			int ret;

			ret = ctf_struct_declaration_list_visit(fd, depth + 1, iter,
				struct_declaration, trace);
			if (ret)
				goto error_free_declaration;
		}
		if (name) {
			int ret;

			ret = bt_register_struct_declaration(g_quark_from_string(name),
					struct_declaration,
					declaration_scope);
			if (ret)
				return NULL;
		}
		return &struct_declaration->p;
	}
error_free_declaration:
	struct_declaration->p.declaration_free(&struct_declaration->p);
error:
	return NULL;
}
