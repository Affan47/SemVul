reload(void)
{
	int res;
	if (AST_RWLIST_WRLOCK(&sinks)) {
		ast_log(AST_LOG_ERROR, "Unable to lock sink list.  Load failed.\n");
		return AST_MODULE_LOAD_DECLINE;
	}

	if ((res = load_config(1))) {
		free_config();
	}

	AST_RWLIST_UNLOCK(&sinks);

	return res ? AST_MODULE_LOAD_DECLINE : AST_MODULE_LOAD_SUCCESS;
}
