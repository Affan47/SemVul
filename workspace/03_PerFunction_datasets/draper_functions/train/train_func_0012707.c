fli_tbox_make_line_selectable( FL_OBJECT * obj,
                               int         line,
                               int         state )
{
    FLI_TBOX_SPEC *sp = obj->spec;
    TBOX_LINE *tl;

    if (    line < 0
         || line >= sp->num_lines
         || sp->lines[ line ]->is_separator
         || obj->type == FL_NORMAL_BROWSER )
        return;

    tl = sp->lines[ line ];
    state = state ? 1 : 0;

    if ( ! state )
    {
        if ( line == sp->select_line )
            sp->select_line = -1;
        if ( line == sp->deselect_line )
            sp->deselect_line = -1;
    }

    if ( tl->selectable != state )
    {
        tl->selectable = state;

        if ( tl->is_special )
        {
            if ( tl->specialGC )
            {
                XFreeGC( flx->display, tl->specialGC );
                sp->lines[ line ]->specialGC = None;
            }

            if ( FL_ObjWin( obj ) )
                tl->specialGC = create_gc( obj, tl->style, tl->size,
                                           state ? obj->lcol : FL_INACTIVE,
                                           sp->x, sp->y, sp->w, sp->h );
        }
    }

    if ( ! sp->no_redraw )
        fl_redraw_object( obj );
}
