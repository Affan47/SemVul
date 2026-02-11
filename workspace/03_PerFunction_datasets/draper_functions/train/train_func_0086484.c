ast_interpret_node(struct lgfs2_lang_state *state,
                                        struct ast_node *ast, struct gfs2_sbd *sbd)
{
	struct lgfs2_lang_result *result = NULL;

	if (ast->ast_type == AST_ST_SET) {
		result = ast_interp_set(state, ast, sbd);
	} else if (ast->ast_type == AST_ST_GET) {
		result = ast_interp_get(state, ast, sbd);
	} else {
		fprintf(stderr, "Invalid AST node type: %d\n", ast->ast_type);
	}
	return result;
}
