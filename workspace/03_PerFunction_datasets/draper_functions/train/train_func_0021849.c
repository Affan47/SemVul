ast_config_destroy(struct ast_config *cfg)
{
	struct ast_category *cat, *catn;

	if (!cfg)
		return;

	ast_includes_destroy(cfg->includes);

	cat = cfg->root;
	while (cat) {
		catn = cat;
		cat = cat->next;
		ast_category_destroy(catn);
	}
	ast_free(cfg);
}
