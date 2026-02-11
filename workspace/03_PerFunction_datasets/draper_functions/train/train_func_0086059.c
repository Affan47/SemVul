gsb_debug_duplicate_budget_check ()
{
    GSList * tmp;
    gint num_duplicate = 0;
    gchar * output = "";

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

	    if ( duplicate && duplicate > tmp_sous_budget )
	    {
	        gchar* tmpstr1 = output;
		gchar* tmpstr2 = g_strdup_printf (
		                        _("In <i>%s</i>, <i>%s</i> is a duplicate of <i>%s</i>.\n"),
					budget -> budget_name,
					((struct_sub_budget *) tmp_sous_budget -> data) -> sub_budget_name,
					((struct_sub_budget *) duplicate -> data) -> sub_budget_name );
		output = g_strconcat ( tmpstr1,
				       tmpstr2,
				       NULL );
		g_free ( tmpstr1 );
		g_free ( tmpstr2 );
		num_duplicate ++;
	    }
	    tmp_sous_budget = tmp_sous_budget -> next;
	}

	tmp = tmp -> next;
    }

    if ( num_duplicate )
    {
	output [ strlen ( output ) - 1 ] = '\0';
	return output;
    }

    return NULL;
}
