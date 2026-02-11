create_yesno( void )
{
    FD_yesno *fdui = malloc( sizeof *fdui );
    int oldy = fli_inverted_y;
    int oldu = fl_get_coordunit( );

    fli_inverted_y = 0;
    fl_set_coordunit( FL_COORD_PIXEL );

    fdui->form = fl_bgn_form( FL_UP_BOX, 460, 130 );
    fl_set_form_title( fdui->form, "Question" );

    fdui->str = fl_add_box( FL_FLAT_BOX, 20, 15, 420, 65, "" );

    fdui->yes = fl_add_button( FL_NORMAL_BUTTON, 85, 90, 80, 27, "Yes" );
    fl_set_button_shortcut( fdui->yes, "Yy", 1 );

    fdui->no = fl_add_button( FL_NORMAL_BUTTON, 295, 90, 80, 27, "No" );
    fl_set_button_shortcut( fdui->no, "Nn", 1 );

    fli_add_q_icon( 10, 20, 33, 33 );

    fl_end_form( );

    fl_register_raw_callback( fdui->form, FL_ALL_EVENT,
                              fli_goodies_preemptive );

    fl_set_form_atclose( fdui->form, fl_goodies_atclose, fdui->no );

    if ( fli_cntl.buttonFontSize != FL_DEFAULT_SIZE )
        fl_fit_object_label( fdui->no, 22, 2 );

    fli_inverted_y = oldy;
    fl_set_coordunit( oldu );

    return fdui;
}
