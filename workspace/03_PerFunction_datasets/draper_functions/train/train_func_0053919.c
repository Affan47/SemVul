AWT_create_tables_admin_window(AW_root *aw_root,GBDATA *gb_main)
{
    static AW_window_simple *aws = 0;

    if (aws) return aws;
    GB_transaction tscope(gb_main);
    create_tables_var(gb_main,aw_root);

    aws = new AW_window_simple;
    aws->init( aw_root, "TABLE_ADMIN","TABLE ADMIN");
    aws->load_xfig("ad_table_admin.fig");

    aws->callback( AW_POPDOWN);
    aws->at("close");
    aws->create_button("CLOSE","CLOSE","C");

    aws->callback( AW_POPUP_HELP,(AW_CL)"tableadm.hlp");
    aws->at("help");
    aws->create_button("HELP","HELP","H");

    aws->button_length(13);

    aws->at("delete");
    aws->callback((AW_CB1)awt_table_delete_cb,(AW_CL)gb_main);
    aws->create_button("DELETE","DELETE","D");

    aws->at("rename");
    aws->callback(AW_POPUP,(AW_CL)create_table_rename_window,(AW_CL)gb_main);
    aws->create_button("RENAME","RENAME","R");

    aws->at("copy");
    aws->callback(AW_POPUP,(AW_CL)create_table_copy_window,(AW_CL)gb_main);
    aws->create_button("COPY","COPY","C");

    aws->at("cmp");
    aws->callback(AW_POPUP,(AW_CL)create_table_create_window,(AW_CL)gb_main);
    aws->create_button("CREATE","CREATE","C");

    aws->at("export");
    aws->callback((AW_CB)create_ad_table_field_admin,(AW_CL)gb_main,0);
    aws->create_button("ADMIN","ADMIN","C");

    aws->at("list");
    awt_create_selection_list_on_tables(gb_main,(AW_window *)aws,AWAR_TABLE_NAME);

    aws->at("rem");
    aws->create_text_field(AWAR_TABLE_REM);

    return (AW_window *)aws;
}
