sqstd_rex_list(SQRex *exp)
{
	SQInteger ret=-1,e;
	if(*exp->_p == SQREX_SYMBOL_BEGINNING_OF_STRING) {
		exp->_p++;
		ret = sqstd_rex_newnode(exp,OP_BOL);
	}
	e = sqstd_rex_element(exp);
	if(ret != -1) {
		exp->_nodes[ret].next = e;
	}
	else ret = e;

	if(*exp->_p == SQREX_SYMBOL_BRANCH) {
		SQInteger temp,tright;
		exp->_p++;
		temp = sqstd_rex_newnode(exp,OP_OR);
		exp->_nodes[temp].left = ret;
		tright = sqstd_rex_list(exp);
		exp->_nodes[temp].right = tright;
		ret = temp;
	}
	return ret;
}
