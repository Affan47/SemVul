find_previous_selectable( FL_OBJECT * obj,
                          int         line )
{
    FLI_TBOX_SPEC *sp = obj->spec;

    if ( line < 0 || line > sp->num_lines )
        line = sp->num_lines;

    while ( --line >= 0 )
        if ( sp->lines[ line ]->selectable )
            break;

    return line;
}
