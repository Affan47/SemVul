create_print_box_for_selection_lists(AW_window *aw_window,AW_CL selid){
    AW_root *aw_root = aw_window->get_root();
    char *data = aw_window->get_selection_list_contents((AW_selection_list *)selid);
    AWT_create_ascii_print_window(aw_root,data,"no title");
    delete data;
}
