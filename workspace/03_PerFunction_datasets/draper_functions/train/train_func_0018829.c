export_nds_cb(AW_window *aww,AW_CL print_flag) {
    GB_transaction  dummy(GLOBAL_gb_main);
    GBDATA         *gb_species;
    const char     *buf;
    AW_root        *aw_root = aww->get_root();
    char           *name    = aw_root->awar(AWAR_EXPORT_NDS"/file_name")->read_string();
    FILE           *out     = fopen(name,"w");

    if (!out) {
        delete name;
        aw_message("Error: Cannot open and write to file");
        return;
    }
    make_node_text_init(GLOBAL_gb_main);
    int   tabbed    = aw_root->awar(AWAR_EXPORT_NDS"/tabbed")->read_int();
    char *tree_name = aw_root->awar(AWAR_TREE)->read_string();

    for (gb_species = GBT_first_marked_species(GLOBAL_gb_main);
         gb_species;
         gb_species = GBT_next_marked_species(gb_species))
    {
        buf = make_node_text_nds(GLOBAL_gb_main, gb_species,(tabbed ? 2 : 1),0, tree_name);
        fprintf(out,"%s\n",buf);
    }
    awt_refresh_selection_box(aw_root, AWAR_EXPORT_NDS);
    fclose(out);
    if (print_flag) {
        GB_ERROR error = GB_textprint(name);
        if (error) aw_message(error);
    }
    free(tree_name);
    free(name);
}
