gsb_data_form_new_organization ( gint account_number )
{
    form_organization *new_form;

    new_form = g_malloc0 (sizeof (form_organization));

    if ( !new_form )
    {
	dialogue_error_memory ();
	return FALSE;
    }

    gsb_data_account_set_form_organization ( account_number,
					     new_form );
    return FALSE;
}
