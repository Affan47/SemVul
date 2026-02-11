fl_set_select_text_font( FL_OBJECT * obj,
                         int         style,
                         int         size )
{
    FLI_SELECT_SPEC *sp;

    if ( obj == NULL )
    {
        M_err( "fl_set_select_font", "NULL object" );
        return -1;
    }

    sp = obj->spec;

    sp->style = style;
    sp->size  = size;
    fl_redraw_object( obj );

    return 0;
}
