push_string(int index, bool trans)
{
	CLASS_CONST cst;
	SYMBOL *sym;
	int len;

	if (index == VOID_STRING)
		len = 0;
	else
	{
		sym = TABLE_get_symbol(EVAL->string, index);
		len = sym->len;
	}

	if (len == 0)
	{
		CODE_push_void_string();
	}
	else if (len == 1)
	{
		CODE_push_char(*(sym->name));
	}
	else
	{
		cst.type = trans ? T_CSTRING : T_STRING;
		cst._string.addr = sym->name;
		cst._string.len = len;

		CODE_push_const(EVAL_add_constant(&cst));
	}
}
