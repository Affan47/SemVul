aw_file_selection( const char *title, const char *dir, const char *def_name, const char *suffix )

{
    aw_assert(0);
    AW_root *root = AW_root::THIS;

    static AW_window_message *aw_msg = 0;
    root->awar_string(AW_FILE_SELECT_TITLE_AWAR)->write_string((char *)title);
    root->awar_string(AW_FILE_SELECT_DIR_AWAR)->write_string((char *)dir);
    root->awar_string(AW_FILE_SELECT_FILE_AWAR)->write_string((char *)def_name);
    root->awar_string(AW_FILE_SELECT_FILTER_AWAR)->write_string((char *)suffix);

    if (!aw_msg) {
        aw_msg = new AW_window_message;

        aw_msg->init( root, "ENTER A STRING", false);

        aw_msg->label_length( 0 );
        aw_msg->button_length( 30 );

        aw_msg->at( 10, 10 );
        aw_msg->auto_space( 10, 10 );
        aw_msg->create_button( 0,AW_FILE_SELECT_TITLE_AWAR );

        aw_msg->at_newline();


        aw_msg->at_newline();

        aw_msg->button_length( 0 );

        aw_msg->callback     ( input_cb, 0 );
        aw_msg->create_button( "OK", "OK", "O" );

        aw_msg->callback     ( input_cb, -1 );
        aw_msg->create_button( "CANCEL", "CANCEL", "C" );

        aw_msg->window_fit();
    }

    aw_msg->show_grabbed();
    char dummy[] = "";
    aw_input_cb_result = dummy;

    root->add_timed_callback_never_disabled(AW_MESSAGE_LISTEN_DELAY, aw_message_timer_listen_event, (AW_CL)aw_msg, 0);
    root->disable_callbacks = true;
    while (aw_input_cb_result == dummy) {
        root->process_events();
    }
    root->disable_callbacks = false;
    aw_msg->hide();

    return aw_input_cb_result;
}
