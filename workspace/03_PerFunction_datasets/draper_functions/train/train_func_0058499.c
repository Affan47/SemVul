handle_canvas( FL_OBJECT * ob,
               int         event,
               FL_Coord    mx   FL_UNUSED_ARG,
               FL_Coord    my   FL_UNUSED_ARG,
               int         key  FL_UNUSED_ARG,
               void      * xev  FL_UNUSED_ARG )
{
    FLI_CANVAS_SPEC *sp = ob->spec;

    switch ( event )
    {
        case FL_DRAW:
            if ( ob->col1 != FL_NoColor )
                sp->xswa.background_pixel = fl_get_pixel( ob->col1 );
            else
                sp->xswa.background_pixel = None;
            sp->mask |= CWBackPixel;
            init_canvas( ob );
            fl_draw_object_label_outside( ob );
            break;

        case FL_FREEMEM:
            fl_hide_canvas( ob );
            free_canvas( ob );
            break;
    }

    return FL_RETURN_NONE;
}
