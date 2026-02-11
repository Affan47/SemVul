switchMemberToContainer (IAnjutaIterable * test)
{
	IAnjutaSymbol *node = IANJUTA_SYMBOL (test);
	IAnjutaIterable *new_container;
	const gchar* sym_type_name =
		ianjuta_symbol_get_string (node, IANJUTA_SYMBOL_FIELD_TYPE_NAME, NULL);

	DEBUG_PRINT ("Switching container with type_name %s", sym_type_name);


	new_container = ianjuta_symbol_query_search (_query_search,
	                                             sym_type_name, NULL);
	if (new_container != NULL)
	{
		g_object_unref (test);

		test = new_container;

		DEBUG_PRINT (".. found new container with n items %d",
		             ianjuta_iterable_get_length (test, NULL));
	}
	else
	{
		DEBUG_PRINT ("Couldn't find a container to substitute sym_type_name %s",
		             sym_type_name);
	}

	return test;
}
