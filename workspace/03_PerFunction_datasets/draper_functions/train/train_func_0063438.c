sqstd_rex_compile(const SQChar *pattern,const SQChar **error)
{
	SQRex *exp = (SQRex *)sq_malloc(sizeof(SQRex));
	exp->_eol = exp->_bol = NULL;
	exp->_p = pattern;
	exp->_nallocated = (SQInteger)scstrlen(pattern) * sizeof(SQChar);
	exp->_nodes = (SQRexNode *)sq_malloc(exp->_nallocated * sizeof(SQRexNode));
	exp->_nsize = 0;
	exp->_matches = 0;
	exp->_nsubexpr = 0;
	exp->_first = sqstd_rex_newnode(exp,OP_EXPR);
	exp->_error = error;
	exp->_jmpbuf = sq_malloc(sizeof(jmp_buf));
	if(setjmp(*((jmp_buf*)exp->_jmpbuf)) == 0) {
		SQInteger res = sqstd_rex_list(exp);
		exp->_nodes[exp->_first].left = res;
		if(*exp->_p!='\0')
			sqstd_rex_error(exp,_SC("unexpected character"));
#ifdef _DEBUG
		{
			SQInteger nsize,i;
			SQRexNode *t;
			nsize = exp->_nsize;
			t = &exp->_nodes[0];
			scprintf(_SC("\n"));
			for(i = 0;i < nsize; i++) {
				if(exp->_nodes[i].type>MAX_CHAR)
					scprintf(_SC("[%02d] %10s "),i,g_nnames[exp->_nodes[i].type-MAX_CHAR]);
				else
					scprintf(_SC("[%02d] %10c "),i,exp->_nodes[i].type);
				scprintf(_SC("left %02d right %02d next %02d\n"),exp->_nodes[i].left,exp->_nodes[i].right,exp->_nodes[i].next);
			}
			scprintf(_SC("\n"));
		}
#endif
		exp->_matches = (SQRexMatch *) sq_malloc(exp->_nsubexpr * sizeof(SQRexMatch));
		memset(exp->_matches,0,exp->_nsubexpr * sizeof(SQRexMatch));
	}
	else{
		sqstd_rex_free(exp);
		return NULL;
	}
	return exp;
}
