data_result_destructor(void *obj)
{
	struct ast_data *root = obj;

	switch (root->type) {
	case AST_DATA_PASSWORD:
	case AST_DATA_STRING:
		ast_free(root->payload.str);
		ao2_ref(root->children, -1);
		break;
	case AST_DATA_POINTER:
	case AST_DATA_CHARACTER:
	case AST_DATA_CONTAINER:
	case AST_DATA_INTEGER:
	case AST_DATA_TIMESTAMP:
	case AST_DATA_SECONDS:
	case AST_DATA_MILLISECONDS:
	case AST_DATA_UNSIGNED_INTEGER:
	case AST_DATA_DOUBLE:
	case AST_DATA_BOOLEAN:
	case AST_DATA_IPADDR:
		ao2_ref(root->children, -1);
		break;
	}
}
