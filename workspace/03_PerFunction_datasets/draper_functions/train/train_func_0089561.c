ast_fax_tech_unregister(struct ast_fax_tech *tech)
{
	struct fax_module *fax;

	ast_verb(3, "Unregistering FAX module type '%s'\n", tech->type);

	AST_RWLIST_WRLOCK(&faxmodules);
	AST_RWLIST_TRAVERSE_SAFE_BEGIN(&faxmodules, fax, list) {
		if (fax->tech != tech) {
			continue;
		}
		AST_RWLIST_REMOVE_CURRENT(list);
		ast_module_unref(ast_module_info->self);
		ast_free(fax);
		ast_verb(4, "Unregistered FAX module type '%s'\n", tech->type);
		break;
	}
	AST_RWLIST_TRAVERSE_SAFE_END;
	AST_RWLIST_UNLOCK(&faxmodules);
}
