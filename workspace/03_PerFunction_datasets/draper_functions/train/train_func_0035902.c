GEN_create_gene_window(AW_root *aw_root) {
    static AW_window_simple_menu *aws = 0;
    if (!aws) {

        aws = new AW_window_simple_menu;
        aws->init( aw_root, "GENE_INFORMATION", "GENE INFORMATION");
        aws->load_xfig("ad_spec.fig");

        aws->button_length(8);

        aws->at("close");
        aws->callback( (AW_CB0)AW_POPDOWN);
        aws->create_button("CLOSE","CLOSE","C");

        aws->at("search");
        aws->callback(AW_POPUP, (AW_CL)GEN_create_gene_query_window, 0);
        aws->create_button("SEARCH","SEARCH","S");

        aws->at("help");
        aws->callback(AW_POPUP_HELP, (AW_CL)"gene_info.hlp");
        aws->create_button("HELP","HELP","H");


        AW_CL scannerid       = awt_create_arbdb_scanner(GLOBAL_gb_main, aws, "box",0,"field","enable",AWT_VIEWER,0,"mark",AWT_NDS_FILTER, &GEN_item_selector);
        ad_global_scannerid   = scannerid;
        ad_global_scannerroot = aws->get_root();

        aws->create_menu("GENE",     "G", "spa_gene.hlp",  AD_F_ALL );
        aws->insert_menu_topic("gene_delete",   "Delete",       "D","spa_delete.hlp",       AD_F_ALL,   (AW_CB)gene_delete_cb, 0, 0);
        aws->insert_menu_topic("gene_rename",   "Rename ...",   "R","spa_rename.hlp",   AD_F_ALL,   AW_POPUP, (AW_CL)create_gene_rename_window, 0);
        aws->insert_menu_topic("gene_copy",     "Copy ...",     "y","spa_copy.hlp",         AD_F_ALL,   AW_POPUP, (AW_CL)create_gene_copy_window, 0);
        aws->insert_menu_topic("gene_create",   "Create ...",   "C","spa_create.hlp",   AD_F_ALL,   AW_POPUP, (AW_CL)create_gene_create_window, 0);
        aws->insert_separator();

        aws->create_menu("FIELDS",     "F", "gene_fields.hlp",  AD_F_ALL );
        GEN_create_field_items(aws);

        {
            Awar_Callback_Info    *cb_info     = new Awar_Callback_Info(aws->get_root(), AWAR_GENE_NAME, GEN_map_gene, scannerid);
            AW_detach_information *detach_info = new AW_detach_information(cb_info);

            cb_info->add_callback();

            aws->at("detach");
            aws->callback(NT_detach_information_window, (AW_CL)&aws, (AW_CL)detach_info);
            aws->create_button("DETACH", "DETACH", "D");

            detach_info->set_detach_button(aws->get_last_widget());
        }


        GEN_map_gene(aws->get_root(),scannerid);
        aws->show();
    }
    else {
        aws->show();
    }

    return aws;
}
