list_copy(const GList* _list)
{
	size_t i;
	GList* newlist = NULL;
	GList* list = UNCONST_CAST_POINTER(GList *, _list);

	for (i = 0; i < g_list_length(list); i++){
		char* dup_element = NULL;
		char* element = g_list_nth_data(list, i);
		int len;
		if (element == NULL){
			cl_log(LOG_WARNING, "list_copy:"
			       "element is NULL");
			continue;
		}

		len = strlen(element);
		dup_element= malloc(len + 1);
		if ( dup_element == NULL){
			cl_log(LOG_ERR, "duplicate element failed");
			continue;
		}
		memcpy(dup_element, element,len);
		dup_element[len] = 0;

		newlist = g_list_append(newlist, dup_element);
	}

	return newlist;
}
