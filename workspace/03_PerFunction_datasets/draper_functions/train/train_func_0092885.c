set_command( const std::string& command, const std::string& arg1, const std::string& arg2 )
{
    if( command == "append_item" ) append_item();
    else if( command == "append_history" ) append_history();
    else if( command == "remove_item" ) remove_item( arg1 );
    else if( command == "remove_headitem" ) remove_headitem();
    else if( command == "remove_allitems" ) remove_allitems();
    else if( command == "edit_tree" ) edit_tree();
    else if( command == "save_xml" ) save_xml();
    else if( command == "toggle_articleicon" ) toggle_articleicon( arg1 );
    else if( command == "toggle_boardicon" ) toggle_boardicon( arg1 );
    else if( command == "replace_thread" ) replace_thread( arg1, arg2 );

    else if( command == "hide_popup" ) m_treeview.hide_popup();

    else if( command == "check_update_root" ) check_update_dir( true, false );
    else if( command == "check_update_open_root" ) check_update_dir( true, true );
    else if( command == "cancel_check_update" ) stop();

    else if( command == "select_item" ) select_item( arg1 );

    return true;
}
