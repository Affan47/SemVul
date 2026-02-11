NT_import_sequences(AW_window *aww,AW_CL,AW_CL){

    if (GLOBAL_gb_merge) {
#if defined(DEBUG)
        AWT_browser_forget_db(GLOBAL_gb_merge);
#endif
        GB_close(GLOBAL_gb_merge);
    }

    AW_root *awr = aww->get_root();

    awr->awar_int(AWAR_READ_GENOM_DB, IMP_PLAIN_SEQUENCE);

    GLOBAL_gb_merge = open_AWTC_import_window(aww->get_root(), "", false, GLOBAL_gb_main, (AW_RCB)nt_seq_load_cb, 0, 0);


    int gb_main_is_genom_db, gb_merge_is_genom_db;
    {
        GB_transaction t1(GLOBAL_gb_main);
        GB_transaction t2(GLOBAL_gb_merge);

        gb_main_is_genom_db  = GEN_is_genome_db(GLOBAL_gb_main, 0);
        gb_merge_is_genom_db = GEN_is_genome_db(GLOBAL_gb_merge, gb_main_is_genom_db);
    }

    nt_assert(gb_main_is_genom_db == gb_merge_is_genom_db);

    awr->awar(AWAR_READ_GENOM_DB)->write_int(gb_main_is_genom_db ? IMP_GENOME_FLATFILE : IMP_PLAIN_SEQUENCE);

    {
        GB_transaction dummy(GLOBAL_gb_main);
        char *ali_name = GBT_get_default_alignment(GLOBAL_gb_main);
        char *ali_type = GBT_get_alignment_type_string(GLOBAL_gb_main, ali_name);

        AWTC_import_set_ali_and_type(awr, ali_name, ali_type, GLOBAL_gb_main);

        free(ali_type);
        free(ali_name);
    }
}
