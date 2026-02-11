gsb_debug_duplicate_budget_fix ()
{
    GSList * tmp;

    tmp = budget_list;
    while ( tmp )
    {
	struct_budget * budget = tmp -> data;
	GSList * tmp_sous_budget = budget -> sub_budget_list;

	while ( tmp_sous_budget )
	{
	    GSList * duplicate;
	    duplicate = g_slist_find_custom ( budget -> sub_budget_list,
					      tmp_sous_budget -> data,
					      (GCompareFunc) gsb_data_sub_budget_compare );
	    if ( duplicate )
	    {
		struct_sub_budget * duplicate_budget = duplicate -> data;

		duplicate_budget -> sub_budget_number = gsb_data_budget_max_sub_budget_number ( budget -> budget_number ) + 1;
	    }
	    tmp_sous_budget = tmp_sous_budget -> next;
	}

	tmp = tmp -> next;
    }

    return TRUE;
}
