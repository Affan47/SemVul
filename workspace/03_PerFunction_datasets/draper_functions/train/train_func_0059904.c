unset_at_commands( void ) {


    _callback   = NULL;
    _d_callback = NULL;

    _at->correct_for_at_string = false;
    _at->correct_for_at_center = 0;
    _at->to_position_exists    = false;
    _at->highlight             = false;

    freeset(_at->helptext_for_next_button, 0);
    freeset(_at->label_for_inputfield, 0);

    _at->background_color = 0;
}
