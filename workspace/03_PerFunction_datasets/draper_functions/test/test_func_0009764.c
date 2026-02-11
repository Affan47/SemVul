try_get_symbol_data(char *symbol, long size, void *local)
{
        struct syment *sp;

        if ((sp = symbol_search(symbol)) &&
            readmem(sp->value, KVADDR, local,
            size, symbol, RETURN_ON_ERROR|QUIET))
			return TRUE;

	return FALSE;
}
