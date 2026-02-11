gsb_form_config_remove_column ( void )
{
    gint row;
    gint account_number;
    gint nb_columns;

    account_number = gsb_account_get_combo_account_number ( accounts_combobox );
    nb_columns = gsb_data_form_get_nb_columns (account_number);

    if ( nb_columns == 1 )
	return FALSE;


    if ( !gsb_form_config_check_for_removing ( account_number,
					       0 ))
	return FALSE;


    nb_columns--;
    gsb_data_form_set_nb_columns ( account_number,
				   nb_columns );


    for ( row=0 ; row< gsb_data_form_get_nb_rows (account_number) ; row++ )
    {
	if ( gsb_data_form_get_value (account_number,
				      nb_columns,
				      row ))
	{


	    gint tmp_row, tmp_column;

	    for ( tmp_row=0 ; tmp_row< gsb_data_form_get_nb_rows (account_number) ; tmp_row++ )
		for ( tmp_column=0 ; tmp_column<nb_columns ; tmp_column++ )
		    if ( !gsb_data_form_get_value ( account_number,
						    tmp_column,
						    tmp_row ))
		    {
			gsb_data_form_set_value ( account_number,
						  tmp_column,
						  tmp_row,
						  gsb_data_form_get_value ( account_number,
									    nb_columns,
									    row ));
			gsb_data_form_set_value ( account_number,
						  nb_columns,
						  row,
						  0 );
			tmp_row = gsb_data_form_get_nb_rows (account_number);
			tmp_column = nb_columns;
		    }
	}
    }


    gsb_data_form_set_width_column ( account_number,
				     nb_columns - 1,
				     gsb_data_form_get_width_column ( account_number,
								      nb_columns )
				     +
				     gsb_data_form_get_width_column ( account_number,
								      nb_columns ));
    gsb_data_form_set_width_column ( account_number,
				     nb_columns,
				     0 );


    gsb_form_config_realized ( form_config_tree_view, NULL );
    if ( etat.modification_fichier == 0 )
        modification_fichier ( TRUE );
    return FALSE;
}
