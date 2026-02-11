store_check_num(struct store *store, const object_type *o_ptr)
{
	int i;
	object_type *j_ptr;


	if (store->stock_num < store->stock_size) return TRUE;


	if (store->sidx == STORE_HOME)
	{

		for (i = 0; i < store->stock_num; i++)
		{

			j_ptr = &store->stock[i];


			if (object_similar(j_ptr, o_ptr, OSTACK_PACK))
				return (TRUE);
		}
	}


	else
	{

		for (i = 0; i < store->stock_num; i++)
		{

			j_ptr = &store->stock[i];


			if (object_similar(j_ptr, o_ptr, OSTACK_STORE))
				return (TRUE);
		}
	}


	return (FALSE);
}
