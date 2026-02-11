create_colorform( void )
{
    int i, j;

    if ( cs->colorform )
        return;

    cs->colorform = fl_bgn_form( FL_UP_BOX, 240, 220 );

    for ( i = 0; i < 8; i++ )
        for ( j = 0; j < 8; j++ )
        {
            cs->col[ 8 * i + j ] = fl_add_button( FL_NORMAL_BUTTON, 40 + j * 20,
                                                  10 + i * 20, 20, 20, "" );
            fl_set_object_boxtype( cs->col[ 8 * i + j ], FL_BORDER_BOX );
            fl_set_object_lcol( cs->col[ 8 * i + j ], 7 );
        }

    cs->prev = fl_add_button( FL_NORMAL_BUTTON, 10, 10, 30, 160, "@4" );
    cs->next = fl_add_button( FL_NORMAL_BUTTON, 200, 10, 30, 160, "@6" );
    cs->cancel = fl_add_button( FL_NORMAL_BUTTON, 80, 180, 140, 30, "Cancel" );
    cs->cindex = fl_add_text( FL_NORMAL_TEXT, 5, 180, 70, 30, "Cancel" );
    fl_set_object_lsize( cs->cindex,FL_TINY_SIZE );
    fl_end_form( );
}
