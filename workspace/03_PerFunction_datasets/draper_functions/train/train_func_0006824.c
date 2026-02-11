simple_symbol_get_arg_list (IJsSymbol *obj)
{
	SimpleSymbol *symbol = SIMPLE_SYMBOL (obj);
	GList* ret = NULL;
	GList* i;
	for (i = symbol->args; i; i = g_list_next (i))
	{
		ret = g_list_append (ret, g_strdup ((gchar*)i->data));
	}
	return ret;
}
