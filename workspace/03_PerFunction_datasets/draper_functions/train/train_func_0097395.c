compileExpr7(void){
	TKVMExprCode_base *l=compileExpr8();
	if (!l) return NULL;
	while(true){
		lexer->skipWS();
		Token token=lexer->next(ID_MODE);
		if (token.str=="*"){
			TKVMExprCode_base *r=compileExpr8();
			if (!r) { lexer->error(RC.S(ERR_COMPILER_PARSE_ERROR_AFTER)+"'*'"); return l; }
			l=new TKVMExprCodeMUL(l, r);
		}else if (token.str=="/"){
			TKVMExprCode_base *r=compileExpr8();
			if (!r) { lexer->error(RC.S(ERR_COMPILER_PARSE_ERROR_AFTER)+"'/'"); return l; }
			l=new TKVMExprCodeDIV(l, r);
		}else if (token.str=="%"){
			TKVMExprCode_base *r=compileExpr8();
			if (!r) { lexer->error(RC.S(ERR_COMPILER_PARSE_ERROR_AFTER)+"'%'"); return l; }
			l=new TKVMExprCodeMOD(l, r);
		}else{
			lexer->UngetChars(token.str.size());
			return l;
		}
	}
}
