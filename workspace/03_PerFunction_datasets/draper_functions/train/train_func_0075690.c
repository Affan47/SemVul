delete_function(PLpgSQL_function *func)
{

	plpgsql_HashTableDelete(func);


	if (func->use_count == 0 && func->fn_cxt)
	{
		MemoryContextDelete(func->fn_cxt);
		func->fn_cxt = NULL;
	}
}
