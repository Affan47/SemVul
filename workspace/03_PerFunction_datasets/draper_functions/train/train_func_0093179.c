create_awt_do_set_list(AW_root *aw_root, struct adaqbsstruct *cbs)
{
    AW_window_simple *aws = 0;
    aws = new AW_window_simple;
    aws->init( aw_root, "SET_DATABASE_FIELD_OF_LISTED","SET MANY FIELDS");
    aws->load_xfig("ad_mset.fig");

    aws->at("close");
    aws->callback( (AW_CB0)AW_POPDOWN);
    aws->create_button("CLOSE", "CLOSE","C");

    aws->at("help");
    aws->callback( AW_POPUP_HELP,(AW_CL)"write_field_list.hlp");
    aws->create_button("HELP", "HELP","H");

    awt_create_selection_list_on_scandb(cbs->gb_main,aws,cbs->awar_setkey, AWT_NDS_FILTER, "box",0, cbs->selector, 20, 10);
    aws->at("create");
    aws->callback((AW_CB)awt_do_set_list,(AW_CL)cbs,0);
    aws->create_button("SET_SINGLE_FIELD_OF_LISTED","WRITE");
    aws->at("do");
    aws->callback((AW_CB)awt_do_set_list,(AW_CL)cbs,1);
    aws->create_button("APPEND_SINGLE_FIELD_OF_LISTED","APPEND");

    aws->at("val");
    aws->create_text_field(cbs->awar_setvalue,2,2);
    return (AW_window *)aws;

}
