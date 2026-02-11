aa_create_alignment(AW_window *aww) {
    GB_ERROR  error = GB_begin_transaction(GLOBAL_gb_main);
    if (!error) {
        char   *name             = aww->get_root()->awar("presets/alignment_dest")->read_string();
        GBDATA *gb_alignment     = GBT_create_alignment(GLOBAL_gb_main,name,0,0,0,"dna");
        if (!gb_alignment) error = GB_await_error();
        else {
            char *nfield = GBS_global_string_copy("%s/data",name);
            error        = GBT_add_new_changekey( GLOBAL_gb_main,nfield,GB_STRING);
            free(nfield);
        }
        free(name);
    }
    GB_end_transaction_show_error(GLOBAL_gb_main, error, aw_message);
}
