same_list_contents (GList *list1, GList *list2)
{
	GList *cur_item1 = list1;
	GList *cur_item2 = list2;

	if (g_list_length (list1) != g_list_length (list2))
	{
		return FALSE;
	}

	while (cur_item1 != NULL)
	{
		if (cur_item1->data != cur_item2->data)
		{
			return FALSE;
		}

		cur_item1 = g_list_next (cur_item1);
		cur_item2 = g_list_next (cur_item2);
	}

	return TRUE;
}
