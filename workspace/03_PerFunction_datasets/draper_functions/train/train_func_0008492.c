gsb_file_load_import_rule ( const gchar **attribute_names,
                        const gchar **attribute_values )
{
    gint i=0;
    gint import_rule_number = 0;

    if ( !attribute_names[i] )
    return;

    import_rule_number = gsb_data_import_rule_new (NULL);

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
        import_rule_number = gsb_data_import_rule_set_new_number ( import_rule_number,
                                           utils_str_atoi (attribute_values[i]));
        i++;
        continue;
    }

    if ( !strcmp ( attribute_names[i],
               "Na" ))
    {
        gsb_data_import_rule_set_name ( import_rule_number,
                        attribute_values[i]);
        i++;
        continue;
    }

    if ( !strcmp ( attribute_names[i],
               "Acc" ))
    {
        gsb_data_import_rule_set_account ( import_rule_number,
                           utils_str_atoi (attribute_values[i]));
        i++;
        continue;
    }

    if ( !strcmp ( attribute_names[i],
               "Cur" ))
    {
        gsb_data_import_rule_set_currency ( import_rule_number,
                            utils_str_atoi (attribute_values[i]));
        i++;
        continue;
    }

    if ( !strcmp ( attribute_names[i],
               "Inv" ))
    {
        gsb_data_import_rule_set_invert ( import_rule_number,
                          utils_str_atoi (attribute_values[i]));
        i++;
        continue;
    }

    if ( !strcmp ( attribute_names[i],
               "Enc" ))
    {
        gsb_data_import_rule_set_charmap ( import_rule_number,
                                  attribute_values[i]);
        i++;
        continue;
    }

    if ( !strcmp ( attribute_names[i],
               "Fil" ))
    {
        gsb_data_import_rule_set_last_file_name ( import_rule_number,
                                  attribute_values[i]);
        i++;
        continue;
    }

    if ( !strcmp ( attribute_names[i],
               "Act" ))
    {
        gsb_data_import_rule_set_action ( import_rule_number,
                          utils_str_atoi (attribute_values[i]));
        i++;
        continue;
    }


    i++;
    }
    while ( attribute_names[i] );
}
