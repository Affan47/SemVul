ast_custom_function_find(const char *name)
{
	struct ast_custom_function *acf = NULL;

	AST_RWLIST_RDLOCK(&acf_root);
	AST_RWLIST_TRAVERSE(&acf_root, acf, acflist) {
		if (!strcmp(name, acf->name))
			break;
	}
	AST_RWLIST_UNLOCK(&acf_root);

	return acf;
}
