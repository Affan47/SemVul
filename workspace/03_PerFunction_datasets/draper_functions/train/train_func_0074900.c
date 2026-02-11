EXP_create_experiment_window(AW_root *aw_root) {
    static AW_window_simple_menu *aws = 0;
    if (aws) return (AW_window *)aws;

    aws = new AW_window_simple_menu;
    aws->init( aw_root, "EXPERIMENT_INFORMATION", "EXPERIMENT INFORMATION");
    aws->load_xfig("ad_spec.fig");

    aws->button_length(8);

    aws->at("close");
    aws->callback( (AW_CB0)AW_POPDOWN);
    aws->create_button("CLOSE","CLOSE","C");

    aws->at("search");
    aws->callback(AW_POPUP, (AW_CL)EXP_create_experiment_query_window, 0);
    aws->create_button("SEARCH","SEARCH","S");

    aws->at("help");
    aws->callback(AW_POPUP_HELP, (AW_CL)"experiment_info.hlp");
    aws->create_button("HELP","HELP","H");


    AW_CL scannerid       = awt_create_arbdb_scanner(GLOBAL_gb_main, aws, "box",0,"field","enable",AWT_VIEWER,0,"mark",AWT_NDS_FILTER, &EXP_item_selector);
    ad_global_scannerid   = scannerid;
    ad_global_scannerroot = aws->get_root();

    aws->create_menu("EXPERIMENT",     "E", "spa_experiment.hlp",  AD_F_ALL );
    aws->insert_menu_topic("experiment_delete", "Delete",     "D","spa_delete.hlp",       AD_F_ALL,   (AW_CB)experiment_delete_cb, 0, 0);
    aws->insert_menu_topic("experiment_rename", "Rename ...", "R","spa_rename.hlp",   AD_F_ALL,   AW_POPUP, (AW_CL)create_experiment_rename_window, 0);
    aws->insert_menu_topic("experiment_copy",   "Copy ...",   "y","spa_copy.hlp",         AD_F_ALL,   AW_POPUP, (AW_CL)create_experiment_copy_window, 0);
    aws->insert_menu_topic("experiment_create", "Create ...", "C","spa_create.hlp",   AD_F_ALL,   AW_POPUP, (AW_CL)create_experiment_create_window, 0);
    aws->insert_separator();

    aws->create_menu("FIELDS",     "F", "experiment_fields.hlp",  AD_F_ALL );
    EXP_create_field_items(aws);

    {
        Awar_Callback_Info    *cb_info     = new Awar_Callback_Info(aws->get_root(), AWAR_EXPERIMENT_NAME, EXP_map_experiment, scannerid);
        AW_detach_information *detach_info = new AW_detach_information(cb_info);
        cb_info->add_callback();

        aws->at("detach");
        aws->callback(NT_detach_information_window, (AW_CL)&aws, (AW_CL)cb_info);
        aws->create_button("DETACH", "DETACH", "D");

        detach_info->set_detach_button(aws->get_last_widget());
    }


    aws->show();
    EXP_map_experiment(aws->get_root(),scannerid);
    return (AW_window *)aws;
}
