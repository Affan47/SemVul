gsb_assistant_payees_modifie_operations ( GSList *sup_payees,
                        gint transaction_number,
                        gint new_payee_number,
                        gboolean save_notes,
                        gboolean extract_num,
                        gboolean is_transaction )
{
    gchar *tmpstr;
    gint payee_number;
    gchar *nombre;
    gboolean question = TRUE;

    payee_number = gsb_data_mix_get_party_number ( transaction_number, is_transaction );
    if ( g_slist_find ( sup_payees, GINT_TO_POINTER ( payee_number ) ) )
    {
        gsb_data_mix_set_party_number ( transaction_number,
                new_payee_number, is_transaction );
        if ( save_notes )
        {
            tmpstr = g_strdup ( gsb_data_mix_get_notes (
                        transaction_number, is_transaction ) );
            if ( tmpstr && strlen ( tmpstr ) )
            {
                overwrite_payee -> message = g_strdup_printf (
                    _("Do you want overwrite the existing note.\n\n"
                    "If you answer YES, the existing note will be replaced by %s."),
                    gsb_data_payee_get_name ( payee_number, TRUE ) );

                if ( question_conditional_yes_no_with_struct (
                 overwrite_payee ) == FALSE )
                    question = FALSE;
                g_free ( tmpstr );
            }
            else
                question = TRUE;
            if ( question && my_strcmp ( (gchar *) gsb_data_payee_get_name (
                payee_number, TRUE ),
                (gchar *) gsb_data_payee_get_name (
                new_payee_number, TRUE ) ) != 0 )
            gsb_data_mix_set_notes ( transaction_number,
                gsb_data_payee_get_name ( payee_number, TRUE ), is_transaction );
        }
        if ( extract_num )
        {
            nombre = gsb_string_extract_int (
                gsb_data_payee_get_name ( payee_number, FALSE ) );
            gsb_data_mix_set_method_of_payment_content (
                transaction_number, nombre, is_transaction );
            g_free ( nombre );
        }
    }
}
