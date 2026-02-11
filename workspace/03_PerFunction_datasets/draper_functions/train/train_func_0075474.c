MG_extended_delete_cb(AW_window *aww, GBDATA *gbmain, int ex_nr) {
    GB_ERROR error = GB_begin_transaction(gbmain);

    if (!error) {
        const char *tsource = GBS_global_string("tmp/merge%i/extended_name", ex_nr);
        char       *source  = aww->get_root()->awar(tsource)->read_string();

        GBDATA *gb_sai    = GBT_find_SAI(gbmain, source);
        if (gb_sai) error = GB_delete(gb_sai);
        else    error     = "Please select a SAI first";

        free(source);
    }
    GB_end_transaction_show_error(gbmain, error, aw_message);
}
