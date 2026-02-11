__ast_cc_config_params_init(const char *file, int line, const char *function)
{
#if defined(__AST_DEBUG_MALLOC)
	struct ast_cc_config_params *params = __ast_malloc(sizeof(*params), file, line, function);
#else
	struct ast_cc_config_params *params = ast_malloc(sizeof(*params));
#endif

	if (!params) {
		return NULL;
	}

	ast_cc_default_config_params(params);
	return params;
}
