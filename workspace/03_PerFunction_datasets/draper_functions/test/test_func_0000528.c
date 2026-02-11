gsb_data_form_dup_organization ( gint origin_account,
					  gint target_account )
{
    form_organization *origin_form;
    form_organization *new_form;

    origin_form = gsb_data_account_get_form_organization (origin_account);

    if ( !origin_form )
	return FALSE;

    new_form = g_malloc0 ( sizeof (form_organization));

     if ( !new_form )
    {
	dialogue_error_memory ();
	return FALSE;
    }

    memcpy ( new_form,
	     origin_form,
	     sizeof (form_organization));

    gsb_data_account_set_form_organization ( target_account,
					     new_form );

    return TRUE;
}
