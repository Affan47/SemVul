handle_clock( FL_OBJECT * ob,
              int         event,
              FL_Coord    x   FL_UNUSED_ARG,
              FL_Coord    y   FL_UNUSED_ARG,
              int         k   FL_UNUSED_ARG,
              void *      ev  FL_UNUSED_ARG )
{
    time_t ticks;
    struct tm *timeofday;
    SPEC *sp = ob->spec;

    switch ( event )
    {
        case FL_DRAW :
            fl_drw_box( ob->boxtype, ob->x, ob->y, ob->w, ob->h,
                        ob->col1, ob->bw );
            if ( ob->type == FL_DIGITAL_CLOCK )
                draw_digitalclock( ob );
            else
                draw_clock( ob->type, ob->x, ob->y, ob->w, ob->h,
                            ob->col1, ob->col2 );


        case FL_DRAWLABEL :
            if ( ! updating )
                fl_drw_text_beside( ob->align & ~ FL_ALIGN_INSIDE,
                                    ob->x, ob->y, ob->w, ob->h,
                                    ob->lcol, ob->lstyle, ob->lsize,
                                    ob->label );
            updating = 0;
            break;

        case FL_STEP:


            if ( ++sp->nstep & 1 )
                break;

            sp->nstep = 0;
            ticks = time( 0 ) + sp->offset;
            if ( ticks != sp->sec )
            {
                updating   = 1;
                sp->sec    = ticks;
                timeofday  = localtime( &ticks );
                seconds    = timeofday->tm_sec;
                hours      = timeofday->tm_hour;
                minutes    = timeofday->tm_min;
                fl_redraw_object( ob );
            }
            break;

        case FL_FREEMEM:
            fl_free( ob->spec );
            break;
    }

    return FL_RETURN_NONE;
}
