scb_initialvalue_change( FL_OBJECT * ob    FL_UNUSED_ARG,
                         long        data  FL_UNUSED_ARG )
{
    double val = get_finput_value( scb_attrib->initial_val );

    fl_set_scrollbar_value( scb_attrib->vdata, val );
    set_finput_value( scb_attrib->initial_val, scb_spec->val, -1 );

    if ( auto_apply )
        redraw_the_form( 0 );
}
