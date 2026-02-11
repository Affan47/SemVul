PH_save_ml_multiline_cb(AW_window *aww) {
    GB_begin_transaction(GLOBAL_gb_main);
    GB_ERROR error = 0;
    char *fname = aww->get_root()->awar("tmp/phylo/markerlinename")->read_string();
    int fname_len = strlen(fname);
    {
        char *digit_appended = (char*)malloc(fname_len+2);
        memcpy(digit_appended, fname, fname_len);
        strcpy(digit_appended+fname_len, "0");

        freeset(fname, digit_appended);
    }
    GBDATA *gb_sai[3];
    int i;
    for (i=0; !error && i<3; i++) {
        fname[fname_len] = '0'+i;
        error = PH_create_ml_multiline_SAI(fname, i, &gb_sai[i]);
    }

    delete fname;

    if (error) {
        GB_abort_transaction(GLOBAL_gb_main);
        aw_message(error);
    }else{
        GB_commit_transaction(GLOBAL_gb_main);
    }
}
