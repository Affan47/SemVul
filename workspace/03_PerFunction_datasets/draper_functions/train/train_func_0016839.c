getoneobj(long index, int symtype)
{
	char *symname;

	if (gettoken() == T_SYMBOL) {
		if (symtype == SYM_UNDEFINED) {
			rescantoken();
			(void) getidexpr(TRUE, 1);
		} else {
			symname = tokensymbol();
			definesymbol(symname, symtype);
			usesymbol(symname, 0);
		}
		getoneobj(index, symtype);
		addop(OP_ASSIGN);
		return;
	}
	rescantoken();
	addopone(OP_OBJCREATE, index);
	while (gettoken() == T_ASSIGN)
		(void) getinitlist();
	rescantoken();
}
