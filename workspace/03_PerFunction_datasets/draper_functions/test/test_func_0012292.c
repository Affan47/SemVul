create_save_box_for_selection_lists(AW_root *aw_root,AW_CL selid)
{
    AW_selection_list *selection_list = (AW_selection_list*)selid;

    char *var_id         = GBS_string_2_key(selection_list->variable_name);
    char *awar_base_name = GBS_global_string_copy("tmp/save_box_sel_%s", var_id);
    char *awar_line_anz  = GBS_global_string_copy("%s/line_anz", awar_base_name);
    {
        aw_create_selection_box_awars(aw_root, awar_base_name, ".", GBS_global_string("noname.list"), "list");
        aw_root->awar_int(awar_line_anz, 0, AW_ROOT_DEFAULT);
    }

    AW_window_simple *aws       = new AW_window_simple;
    char             *window_id = GBS_global_string_copy("SAVE_SELECTION_BOX_%s", var_id);

    aws->init(aw_root, window_id, "SAVE BOX");
    aws->load_xfig("sl_s_box.fig");

    aws->at("close");aws->callback((AW_CB0)AW_POPDOWN);
    aws->create_button("CLOSE", "CLOSE","C");

    aws->at("save");
    aws->highlight();
    aws->callback(create_save_box_for_selection_lists_save,selid,(AW_CL)awar_base_name);
    aws->create_button("SAVE", "SAVE","S");

    aws->at("nlines");
    aws->create_option_menu(awar_line_anz, 0, "");
    aws->insert_default_option("all","a",0);
    aws->insert_option(   "50", "a",    50);
    aws->insert_option(  "100", "a",   100);
    aws->insert_option(  "500", "a",   500);
    aws->insert_option( "1000", "a",  1000);
    aws->insert_option( "5000", "a",  5000);
    aws->insert_option("10000", "a", 10000);
    aws->update_option_menu();

    awt_create_selection_box(aws,awar_base_name);

    free(window_id);
    free(awar_line_anz);
    free(var_id);

    return aws;
}
