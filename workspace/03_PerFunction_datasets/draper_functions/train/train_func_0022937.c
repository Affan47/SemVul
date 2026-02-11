free_match_expression(match_expression *expr)
{
	if (expr) {
		switch(expr->op) {
			case MATCH_EXPR_OR:
			case MATCH_EXPR_AND:
				free_match_expression(expr->left);
				free_match_expression(expr->right);
				break;
			case MATCH_EXPR_LEAF:
				free_match_operation(expr->match);
				break;
		}
		free(expr);
	}
}
