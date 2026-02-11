DI_create_save_matrix_window(AW_root *aw_root, char *base_name)
{
    static AW_window_simple *aws = 0;
    if (aws) return aws;
    aws = new AW_window_simple;
    aws->init( aw_root, "SAVE_MATRIX", "Save Matrix");
    aws->load_xfig("sel_box.fig");

    aws->at("close");aws->callback((AW_CB0)AW_POPDOWN);
    aws->create_button("CLOSE", "CANCEL","C");


    aws->at("help");aws->callback(AW_POPUP_HELP,(AW_CL)"save_matrix.hlp");
    aws->create_button("HELP", "HELP","H");

    aws->at("user");
    aws->create_option_menu(AWAR_DIST_SAVE_MATRIX_TYPE);
    aws->insert_default_option("Phylip Format (Lower Triangular Matrix)","P",DI_SAVE_PHYLIP_COMP);
    aws->insert_option("Readable (using NDS)","R",DI_SAVE_READABLE);
    aws->insert_option("Tabbed (using NDS)","R",DI_SAVE_TABBED);
    aws->update_option_menu();

    awt_create_selection_box((AW_window *)aws,base_name);

    aws->at("save2");aws->callback(di_save_matrix_cb);
    aws->create_button("SAVE", "SAVE","S");

    aws->callback( (AW_CB0)AW_POPDOWN);
    aws->at("cancel2");
    aws->create_button("CLOSE", "CANCEL","C");

    return aws;
}
