ast_config_copy(const struct ast_config *old)
{
	struct ast_config *new_config = ast_config_new();
	struct ast_category *cat_iter;

	if (!new_config) {
		return NULL;
	}

	for (cat_iter = old->root; cat_iter; cat_iter = cat_iter->next) {
		struct ast_category *new_cat =
			ast_category_new(cat_iter->name, cat_iter->file, cat_iter->lineno);
		if (!new_cat) {
			goto fail;
		}
		ast_category_append(new_config, new_cat);
		if (cat_iter->root) {
			new_cat->root = ast_variables_dup(cat_iter->root);
			if (!new_cat->root) {
				goto fail;
			}
			new_cat->last = cat_iter->last;
		}
	}

	return new_config;

fail:
	ast_config_destroy(new_config);
	return NULL;
}
