gsb_data_form_set_value ( gint account_number,
				   gint column,
				   gint row,
				   gint value )
{
    form_organization *form;

    form = gsb_data_account_get_form_organization ( account_number );

    if ( !form
	 ||
	 column > MAX_WIDTH
	 ||
	 row > MAX_HEIGHT)
	return FALSE;

    form -> form_table[row][column] = value;
    return TRUE;
}
