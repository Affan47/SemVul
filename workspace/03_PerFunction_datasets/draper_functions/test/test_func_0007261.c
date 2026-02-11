sqstd_rex_charnode(SQRex *exp,SQBool isclass)
{
	SQChar t;
	if(*exp->_p == SQREX_SYMBOL_ESCAPE_CHAR) {
		exp->_p++;
		switch(*exp->_p) {
			case 'n': exp->_p++; return sqstd_rex_newnode(exp,'\n');
			case 't': exp->_p++; return sqstd_rex_newnode(exp,'\t');
			case 'r': exp->_p++; return sqstd_rex_newnode(exp,'\r');
			case 'f': exp->_p++; return sqstd_rex_newnode(exp,'\f');
			case 'v': exp->_p++; return sqstd_rex_newnode(exp,'\v');
			case 'a': case 'A': case 'w': case 'W': case 's': case 'S':
			case 'd': case 'D': case 'x': case 'X': case 'c': case 'C':
			case 'p': case 'P': case 'l': case 'u':
				{
				t = *exp->_p; exp->_p++;
				return sqstd_rex_charclass(exp,t);
				}
			case 'b':
			case 'B':
				if(!isclass) {
					SQInteger node = sqstd_rex_newnode(exp,OP_WB);
					exp->_nodes[node].left = *exp->_p;
					exp->_p++;
					return node;
				}
			default:
				t = *exp->_p; exp->_p++;
				return sqstd_rex_newnode(exp,t);
		}
	}
	else if(!scisprint(*exp->_p)) {

		sqstd_rex_error(exp,_SC("letter expected"));
	}
	t = *exp->_p; exp->_p++;
	return sqstd_rex_newnode(exp,t);
}
