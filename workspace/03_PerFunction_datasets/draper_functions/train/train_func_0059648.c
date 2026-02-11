awt_table_field_hide_cb(AW_window *aws, awt_table *awtt) {
    GB_begin_transaction(awtt->gb_main);
    GB_ERROR  error    = 0;
    GBDATA   *gb_table = GBT_open_table(awtt->gb_main, awtt->table_name,GB_TRUE);

    if (!gb_table){
        error = GBS_global_string("Table '%s' does not exist",awtt->table_name);
    }
    else {
        char   *source    = aws->get_root()->awar(awtt->awar_selected_field)->read_string();
        GBDATA *gb_source = GBT_find_table_field(gb_table,source);

        if (!gb_source) error = "Please select an item you want to delete";
        else error            = GB_delete(gb_source);

        free(source);
    }
    GB_end_transaction_show_error(awtt->gb_main, error, aw_message);
}
