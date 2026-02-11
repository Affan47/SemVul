convertTokenToNode(struct toc* t){
	if(t == NULL){
		return -1;
	}

	switch(t->type){
		case T_EQV:
			return AST_EQV;
		case T_NEQV:
			return AST_NEQV;
		case T_GRT:
			return AST_GRT;
		case T_LSS:
			return AST_LSS;
		case T_GEQV:
			return AST_GEQV;
		case T_LEQV:
			return AST_LEQV;
		case T_ADD:
			return AST_ADD;
		case T_SUB:
			return AST_SUB;
		case T_OR:
			return AST_OR;
		case T_XOR:
			return AST_XOR;
		case T_MUL:
			return AST_MUL;
		case T_DIV:
			return AST_DIV;
		case T_AND:
			return AST_AND;
		case T_NOT:
			return AST_NOT;
		case T_NMB:
			return AST_NUM;
		case T_TEXT:
			return AST_STR;
		case T_ID:
			return AST_ID;

		default:
			return -1;
	}
}
