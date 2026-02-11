ast_lookup_block_num(struct ast_node *ast, struct gfs2_sbd *sbd)
{
	uint64_t bn = 0;
	switch (ast->ast_type) {
	case AST_EX_OFFSET:
		bn = ast_lookup_block_num(ast->ast_left, sbd) + ast->ast_num;
		break;
	case AST_EX_ADDRESS:
		if (gfs2_check_range(sbd, ast->ast_num))
			break;
		bn = ast->ast_num;
		break;
	case AST_EX_PATH:
		bn = ast_lookup_path(ast->ast_str, sbd);
		break;
	case AST_EX_ID:
		bn = ast_lookup_id(ast->ast_str, sbd);
		break;
	case AST_EX_SUBSCRIPT:
		bn = ast_lookup_subscript(ast->ast_left, ast->ast_left->ast_left, sbd);
		break;
	default:
		break;
	}
	return bn;
}
