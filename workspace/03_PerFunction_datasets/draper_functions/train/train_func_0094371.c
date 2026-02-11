fl_set_input_cursorpos( FL_OBJECT * obj,
                        int         xpos,
                        int         ypos )
{
    FLI_INPUT_SPEC *sp = obj->spec;
    int newp,
        len;

    if ( obj->type == FL_HIDDEN_INPUT )
        return;

    if ( ypos < 1 )
        ypos = 1;
    else if ( ypos > sp->lines )
        ypos = sp->lines;

    if ( xpos < 0 )
        xpos = 0;

    len = strlen( sp->str );

    newp = xytopos( sp, xpos, ypos, len );

    if ( newp > len )
        newp = len;

    if ( newp != sp->position )
    {
        sp->position = newp;
        if ( ! make_line_visible( obj, sp->ypos ) )
            fl_redraw_object( sp->input );
    }
}
