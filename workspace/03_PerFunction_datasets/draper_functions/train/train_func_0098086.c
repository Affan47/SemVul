bet_data_hist_add_div ( gint account_number,
                        gint div_number,
                        gint sub_div_nb )
{
    gchar *key;
    gchar *sub_key;
    struct_hist_div *shd;

    key = bet_data_get_key ( account_number, div_number );

    if ( ( shd = g_hash_table_lookup ( bet_hist_div_list, key ) ) )
    {
        shd -> div_edited = FALSE;
        shd -> amount = null_real;

        if ( sub_div_nb > 0 )
        {
            sub_key = utils_str_itoa ( sub_div_nb );
            if (  !g_hash_table_lookup ( shd -> sub_div_list, sub_key ) )
            {
                struct_hist_div *sub_shd;

                sub_shd = struct_initialise_hist_div ( );
                if ( !sub_shd )
                {
                    dialogue_error_memory ( );
                    return FALSE;
                }
                sub_shd -> div_number = sub_div_nb;
                g_hash_table_insert ( shd -> sub_div_list, sub_key, sub_shd );
            }
            else
            {
                shd -> div_edited = FALSE;
                shd -> amount = null_real;
            }
        }
    }
    else
    {
        shd = struct_initialise_hist_div ( );
        if ( !shd )
        {
            dialogue_error_memory ( );
            return 0;
        }
        shd -> account_nb = account_number;
        shd -> origin = gsb_data_account_get_bet_hist_data ( account_number );
        shd -> div_number = div_number;
        if ( sub_div_nb > 0 )
        {
            struct_hist_div *sub_shd;

            sub_shd = struct_initialise_hist_div ( );
            if ( !sub_shd )
            {
                dialogue_error_memory ( );
                return FALSE;
            }
            sub_key = utils_str_itoa ( sub_div_nb );
            sub_shd -> div_number = sub_div_nb;
            g_hash_table_insert ( shd -> sub_div_list, sub_key, sub_shd );
        }
        g_hash_table_insert ( bet_hist_div_list, key, shd );
    }

    return TRUE;
}
