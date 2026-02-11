check_stmt_level(ast *a, symtab *st){

	ast *body = a;


	 	ast_node_type t2n = ast_get_node_type(body);
		switch(t2n){

		case AST_NODE_BINARY:
			check_bin(body,st);
			break;

		case AST_NODE_UNARY:
			check_unary(body);
			break;

		case AST_NODE_FUNCTION_CALL:
			check_func_call(body, st);
			break;

		case AST_NODE_CONDITIONAL:
			check_conditional(body, st);
			break;

		case AST_NODE_WHILE:
			check_while(body, st);
			break;

		case AST_NODE_RETURN:
			check_return(body);
			break;


		case AST_NODE_SPAWN:
			check_spawn(body, st);
			break;

		case AST_NODE_DECLARATION:
			break;


		 case AST_NODE_LOCK:
			return check_lock(body, st);
			break;

		case AST_NODE_STATEMENT:
			check_stmt(body, st);
			break;


		default:
			break;
		}

}
