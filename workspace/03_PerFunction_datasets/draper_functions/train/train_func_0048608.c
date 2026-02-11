select_object_by_class( int cn )
{
    int i;

    for ( i = 0; i < cnumb; i++ )
        if ( classes[ i ].cn == cn )
        {
            fl_select_browser_line( fd_control->objectbrowser,
                                    classes[ i ].bline );
            fl_show_browser_line( fd_control->objectbrowser,
                                  classes[ i ].bline );
            cur_class = cn;
            break;
        }
}
