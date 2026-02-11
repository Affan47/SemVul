gsb_file_save_import_rule_part ( gulong iterator,
                        gulong *length_calculated,
                        gchar **file_content )
{
    GSList *list_tmp;

    list_tmp = gsb_data_import_rule_get_list ();

    while ( list_tmp )
    {
	gchar *new_string;
	gint import_rule_number;

	import_rule_number = gsb_data_import_rule_get_number (list_tmp -> data);

	new_string = g_markup_printf_escaped ( "\t<Import_rule Nb=\"%d\" Na=\"%s\" Acc=\"%d\" "
                           "Cur=\"%d\" Inv=\"%d\" Enc=\"%s\" Fil=\"%s\" Act=\"%d\" />\n",
					       import_rule_number,
					       my_safe_null_str(gsb_data_import_rule_get_name (import_rule_number)),
					       gsb_data_import_rule_get_account (import_rule_number),
					       gsb_data_import_rule_get_currency (import_rule_number),
					       gsb_data_import_rule_get_invert (import_rule_number),
					       my_safe_null_str(gsb_data_import_rule_get_charmap (import_rule_number)),
					       my_safe_null_str(gsb_data_import_rule_get_last_file_name (import_rule_number)),
					       gsb_data_import_rule_get_action (import_rule_number));


	iterator = gsb_file_save_append_part ( iterator,
					       length_calculated,
					       file_content,
					       new_string );
	list_tmp = list_tmp -> next;
    }
    return iterator;
}
