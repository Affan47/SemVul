ast_destroy(struct ast_node **node)
{
	if (*node == NULL) {
		return;
	}
	ast_destroy(&(*node)->ast_left);
	ast_destroy(&(*node)->ast_right);
	switch((*node)->ast_type) {
	case AST_EX_ID:
	case AST_EX_PATH:
	case AST_EX_STRING:
		free((*node)->ast_str);
		break;
	default:
		break;
	}
	free((*node)->ast_text);
	free(*node);
	*node = NULL;
}
