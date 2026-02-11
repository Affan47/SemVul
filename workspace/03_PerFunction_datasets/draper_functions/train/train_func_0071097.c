fl_set_input_selected( FL_OBJECT * obj,
                       int         yes )
{
    FLI_INPUT_SPEC *sp = obj->spec;

    if ( obj->type == FL_HIDDEN_INPUT )
        return;

    if ( yes )
    {
        sp->position = sp->endrange = strlen( sp->str );
        sp->beginrange = 0;
    }
    else
        sp->endrange = -1;

    fl_redraw_object( sp->input );
}
