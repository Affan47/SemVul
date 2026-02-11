camel_folder_search_free_result (CamelFolderSearch *search,
                                 GPtrArray *result)
{
	if (!result)
		return;

	g_ptr_array_foreach (result, (GFunc) camel_pstring_free, NULL);
	g_ptr_array_free (result, TRUE);
}
