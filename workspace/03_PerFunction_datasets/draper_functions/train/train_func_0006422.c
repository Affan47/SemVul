cli_fax_show_capabilities(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	struct fax_module *fax;
	unsigned int num_modules = 0;

	switch (cmd) {
	case CLI_INIT:
		e->command = "fax show capabilities";
		e->usage =
			"Usage: fax show capabilities\n"
			"       Shows the capabilities of the registered FAX technology modules\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	ast_cli(a->fd, "\n\nRegistered FAX Technology Modules:\n\n");
	AST_RWLIST_RDLOCK(&faxmodules);
	AST_RWLIST_TRAVERSE(&faxmodules, fax, list) {
		ast_cli(a->fd, "%-15s : %s\n%-15s : %s\n%-15s : ", "Type", fax->tech->type, "Description", fax->tech->description, "Capabilities");
		fax->tech->cli_show_capabilities(a->fd);
		num_modules++;
	}
	AST_RWLIST_UNLOCK(&faxmodules);
	ast_cli(a->fd, "%d registered modules\n\n", num_modules);

	return CLI_SUCCESS;
}
