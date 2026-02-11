gene_rename_cb(AW_window *aww) {
    AW_root *aw_root = aww->get_root();
    char    *source  = aw_root->awar(AWAR_GENE_NAME)->read_string();
    char    *dest    = aw_root->awar(AWAR_GENE_DEST)->read_string();

    if (strcmp(source, dest) != 0) {
        GB_ERROR error = GB_begin_transaction(GLOBAL_gb_main);

        if (!error) {
            GBDATA *gb_gene_data = GEN_get_current_gene_data(GLOBAL_gb_main, aww->get_root());

            if (!gb_gene_data) error = "Please select a species";
            else {
                GBDATA *gb_source = GEN_find_gene_rel_gene_data(gb_gene_data, source);
                GBDATA *gb_dest   = GEN_find_gene_rel_gene_data(gb_gene_data, dest);

                if (!gb_source) error   = "Please select a gene first";
                else if (gb_dest) error = GB_export_errorf("Gene '%s' already exists", dest);
                else {
                    GBDATA *gb_name = GB_search(gb_source, "name", GB_STRING);

                    if (!gb_name) error = GB_await_error();
                    else {
                        error = GB_write_string(gb_name, dest);
                        if (!error) aww->get_root()->awar(AWAR_GENE_NAME)->write_string(dest);
                    }
                }
            }
        }

        error = GB_end_transaction(GLOBAL_gb_main, error);
        aww->hide_or_notify(error);
    }

    free(source);
    free(dest);
}
