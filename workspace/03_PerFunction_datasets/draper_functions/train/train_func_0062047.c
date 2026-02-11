gsb_data_budget_get_sub_budget_number_by_name ( gint budget_number,
                        const gchar *name,
                        gboolean create )
{
    GSList *list_tmp;
    struct_budget *budget;
    gint sub_budget_number = 0;

    if (!name || !strlen (name))
	return FALSE;

    budget = gsb_data_budget_get_structure ( budget_number );

    if (!budget)
	return FALSE;

    list_tmp = g_slist_find_custom ( budget -> sub_budget_list,
				     name,
				     (GCompareFunc) gsb_data_budget_get_pointer_from_sub_name_in_glist );

    if ( list_tmp )
    {
        struct_sub_budget *sub_budget;

        sub_budget = list_tmp -> data;
        sub_budget_number = sub_budget -> sub_budget_number;
    }
    else
    {
        if ( create )
        {
            sub_budget_number = gsb_data_budget_new_sub_budget ( budget_number, name );
            gsb_budget_update_combofix ( FALSE );
        }
    }
    return sub_budget_number;
}
