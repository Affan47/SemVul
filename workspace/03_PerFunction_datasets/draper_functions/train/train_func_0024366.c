gsb_data_budget_new_sub_budget_with_number ( gint number,
                        gint budget_number)
{
    struct_budget *budget;
    struct_sub_budget *sub_budget;

    budget = gsb_data_budget_get_structure ( budget_number );

    if (!budget)
	return 0;

    sub_budget = g_malloc0 ( sizeof (struct_sub_budget));
    sub_budget -> sub_budget_number = number;
    sub_budget -> mother_budget_number = budget_number;

    budget -> sub_budget_list = g_slist_append ( budget -> sub_budget_list,
						 sub_budget );

    sub_budget_buffer = sub_budget;

    return sub_budget -> sub_budget_number;
}
