load_module(void)
{
	ast_format_set(&wav_f.format, AST_FORMAT_SLINEAR, 0);
	ast_format_set(&wav16_f.format, AST_FORMAT_SLINEAR16, 0);
	if (ast_format_def_register(&wav_f)
		|| ast_format_def_register(&wav16_f))
		return AST_MODULE_LOAD_FAILURE;
	return AST_MODULE_LOAD_SUCCESS;
}
