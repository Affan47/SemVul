bet_data_synchronise_hist_div_list ( GHashTable  *list_div )
{
    GHashTableIter iter;
    gpointer key, value;
    SH *sh = NULL;

    g_hash_table_iter_init ( &iter, bet_hist_div_list );
    while ( g_hash_table_iter_next ( &iter, &key, &value ) )
    {
        struct_hist_div *shd = ( struct_hist_div* ) value;
        GHashTableIter new_iter;

        sh = g_hash_table_lookup ( list_div, utils_str_itoa ( shd -> div_number ) );
        if ( sh == NULL )
            bet_data_remove_div_hist ( shd -> account_nb, shd -> div_number, 0 );
        else
        {
            g_hash_table_iter_init ( &new_iter, shd -> sub_div_list );
            while ( g_hash_table_iter_next ( &new_iter, &key, &value ) )
            {
                struct_hist_div *sub_shd = ( struct_hist_div* ) value;

                if ( !g_hash_table_lookup ( sh -> list_sub_div, utils_str_itoa (
                 sub_shd -> div_number ) ) )
                {
                    bet_data_remove_div_hist ( shd -> account_nb,
                                shd -> div_number,
                                sub_shd -> div_number );
                    g_hash_table_iter_init ( &new_iter, shd -> sub_div_list );
                }
            }
        }
    }
}
