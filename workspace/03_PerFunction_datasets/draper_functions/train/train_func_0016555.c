push_string(int index, bool trans)
{
	TRANS_DECL decl;
	SYMBOL *sym;
	int len;

	if (index == VOID_STRING)
		len = 0;
	else
	{
		sym = TABLE_get_symbol(JOB->class->string, index);
		len = sym->len;
	}

	if (len == 0)
	{
		CODE_push_void_string();
	}
	else if (len == 1 && !trans)
	{
		CODE_push_char(*(sym->name));
	}
	else
	{


		if (trans)
			decl.type = TYPE_make(T_CSTRING, 0, 0);
		else
			decl.type = TYPE_make(T_STRING, 0, 0);
		decl.index = NO_SYMBOL;
		decl.value = index;

		CODE_push_const(CLASS_add_constant(JOB->class, &decl));
	}
}
