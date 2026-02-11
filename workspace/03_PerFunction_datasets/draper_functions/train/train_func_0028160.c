awt_open_macro_window(AW_root *aw_root,const char *application_id){
    static AW_window_simple *aws = 0;

    if (!aws) {
        aws = new AW_window_simple;
        aws->init( aw_root, "MACROS", "MACROS");
        aws->load_xfig("macro_select.fig");

        aw_create_selection_box_awars(aw_root, AWAR_MACRO_BASE, ".", ".amc", "");

        aw_root->awar_string(AWAR_MACRO_RECORDING_MACRO_TEXT,"RECORD");

        aws->at("close");aws->callback((AW_CB0)AW_POPDOWN);
        aws->create_button("CLOSE", "CLOSE","C");

        aws->at("help");aws->callback(AW_POPUP_HELP,(AW_CL)"macro.hlp");
        aws->create_button("HELP", "HELP");

        aws->at("start");aws->callback((AW_CB1)awt_start_macro_cb,(AW_CL)application_id);
        aws->create_button(0, AWAR_MACRO_RECORDING_MACRO_TEXT);

        aws->at("delete");aws->callback(awt_delete_macro_cb);
        aws->create_button("DELETE", "DELETE");

        aws->at("edit");aws->callback(awt_edit_macro_cb);
        aws->create_button("EDIT", "EDIT");

        aws->at("exec");aws->callback(awt_exec_macro_cb);
        aws->create_button("EXECUTE", "EXECUTE");

        awt_create_selection_box((AW_window *)aws,AWAR_MACRO_BASE,"","ARBMACROHOME^ARBMACRO");
    }
    return aws;
}
