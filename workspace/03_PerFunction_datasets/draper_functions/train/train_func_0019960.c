transdna_event(AW_window *aww) {
    AW_root  *aw_root      = aww->get_root();
    char     *ali_source   = aw_root->awar(AWAR_TRANSPRO_DEST)->read_string();
    char     *ali_dest     = aw_root->awar(AWAR_TRANSPRO_SOURCE)->read_string();
    long      neededLength = -1;
    bool      retrying     = false;
    GB_ERROR  error        = 0;

    while (!error && neededLength) {
        error = GB_begin_transaction(GLOBAL_gb_main);
        if (!error) error = arb_transdna(GLOBAL_gb_main,ali_source,ali_dest, &neededLength);
        error = GB_end_transaction(GLOBAL_gb_main, error);

        if (!error && neededLength>0) {
            if (retrying || !aw_ask_sure(GBS_global_string("Increase length of '%s' to %li?", ali_dest, neededLength))) {
                error = GBS_global_string("Missing %li columns in alignment '%s'", neededLength, ali_dest);
            }
            else {
                error             = GB_begin_transaction(GLOBAL_gb_main);
                if (!error) error = GBT_set_alignment_len(GLOBAL_gb_main, ali_dest, neededLength);
                error             = GB_end_transaction(GLOBAL_gb_main, error);

                if (!error) {
                    aw_message(GBS_global_string("Alignment length of '%s' has been set to %li\n"
                                                 "running re-aligner again!",
                                                 ali_dest, neededLength));
                    retrying     = true;
                    neededLength = -1;
                }
            }
        }
    }

    if (error) aw_message(error);
    free(ali_dest);
    free(ali_source);
}
