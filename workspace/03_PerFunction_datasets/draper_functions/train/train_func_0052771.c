gsb_data_budget_new ( const gchar *name )
{
    gint budget_number;


    budget_number = gsb_data_budget_new_with_number ( gsb_data_budget_max_number () + 1 );


    if (name)
	gsb_data_budget_set_name ( budget_number,
				   name );
    return budget_number;
}
