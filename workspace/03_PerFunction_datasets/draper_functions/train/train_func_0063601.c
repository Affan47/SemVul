ast_spawn_var_check(ast *a, struct ast_spawn_var_ptr *vars, ast* spawn){
 	if (a == NULL) return;

 	switch(a->node_type){
 		case AST_NODE_BINARY:

 			break;

 		case AST_NODE_DECLARATION:
	 		ast_spawn_add_new_var(a->data.dec.var, vars);
	 		break;

 		case AST_NODE_LEAF:
	 		ast_spawn_add_old_var(a, vars, spawn);
	 		break;


 		default:
 			break;
 	}
 }
