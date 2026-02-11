gsb_file_load_budgetary ( const gchar **attribute_names,
                        const gchar **attribute_values )
{
    gint i=0;
    gint budget_number = 0;

    if ( !attribute_names[i] )
    return;

    do
    {


    if ( !strcmp (attribute_values[i],
              "(null)"))
    {
        i++;
        continue;
    }

    if ( !strcmp ( attribute_names[i],
               "Nb" ))
    {
        budget_number = gsb_data_budget_new_with_number ( utils_str_atoi (attribute_values[i]));

        i++;
        continue;
    }

    if ( !strcmp ( attribute_names[i],
               "Na" ))
    {
        gsb_data_budget_set_name ( budget_number,
                             attribute_values[i]);
        i++;
        continue;
    }

    if ( !strcmp ( attribute_names[i],
                                   "Kd" ))
    {
        gsb_data_budget_set_type ( budget_number,
                                                                                         utils_str_atoi (attribute_values[i]));
        i++;
        continue;
    }


    i++;
    }
    while ( attribute_names[i] );
}
