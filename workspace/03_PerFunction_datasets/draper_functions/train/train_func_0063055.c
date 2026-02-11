set_form( int numb )
{
    if ( numb == -1 )
    {
        cur_form = NULL;
        fl_deselect_browser( fd_control->formbrowser );
    }
    else
    {
        cur_form = forms[ numb ].form;
        set_bounding_box( 0, 0, cur_form->w, cur_form->h );
        fl_select_browser_line( fd_control->formbrowser, numb + 1 );
        fl_winstepsize( main_window, 1, 1 );
        fl_winresize( main_window, cur_form->w, cur_form->h );
        if ( fl_display )
            XSync( fl_display, 0 );
    }

    clear_selection( );
    fillin_groups( );
    redraw_the_form( 1 );
}
