gsb_bank_update_form ( gint bank_number,
                        GtkWidget *frame )
{
    gboolean value;


    gsb_autofunc_entry_set_value ( bank_name, gsb_data_bank_get_name (bank_number), bank_number);
    gsb_autofunc_entry_set_value ( bank_code, gsb_data_bank_get_code (bank_number), bank_number);
    gsb_autofunc_entry_set_value ( bank_BIC, gsb_data_bank_get_bic (bank_number), bank_number);

    gsb_autofunc_entry_set_value ( bank_tel, gsb_data_bank_get_bank_tel (bank_number), bank_number);
    gsb_autofunc_entry_set_value ( bank_mail, gsb_data_bank_get_bank_mail (bank_number), bank_number);
    gsb_autofunc_entry_set_value ( bank_web, gsb_data_bank_get_bank_web (bank_number), bank_number);

    gsb_autofunc_entry_set_value ( bank_contact_name, gsb_data_bank_get_correspondent_name (bank_number), bank_number);
    gsb_autofunc_entry_set_value ( bank_contact_tel, gsb_data_bank_get_correspondent_tel (bank_number), bank_number);
    gsb_autofunc_entry_set_value ( bank_contact_mail, gsb_data_bank_get_correspondent_mail (bank_number), bank_number);
    gsb_autofunc_entry_set_value ( bank_contact_fax, gsb_data_bank_get_correspondent_fax (bank_number), bank_number);

    gsb_autofunc_textview_set_value ( bank_adr, gsb_data_bank_get_bank_address (bank_number), bank_number );
    gsb_autofunc_textview_set_value ( bank_notes, gsb_data_bank_get_bank_note (bank_number), bank_number );


    if (bank_number == -1)
	value = FALSE;
    else
	value = TRUE;
    gtk_widget_set_sensitive ( frame, value );

    if ( GTK_IS_WIDGET(delete_bank_button))
	gtk_widget_set_sensitive ( delete_bank_button, value );

    return FALSE;
}
