draw_timer( FL_OBJECT * ob )
{
    FL_COLOR col;
    char *str;
    SPEC *sp = ob->spec;

    if ( ob->type == FL_HIDDEN_TIMER )
        return;

    if ( ! sp->on || sp->time_left > 0.0 )
        col = ob->col1;
    else if ( ( int ) ( sp->time_left / FL_TIMER_BLINKRATE ) % 2 )
        col = ob->col1;
    else
        col = ob->col2;

    fl_drw_box( ob->boxtype, ob->x, ob->y, ob->w, ob->h, col, ob->bw );

    if ( ob->type == FL_VALUE_TIMER && sp->time_left > 0.0 )
    {
        double time_shown = sp->up ? sp->timer - sp->time_left : sp->time_left;

        str = ( sp->filter ? sp->filter : default_filter )( ob, time_shown );
        fl_drw_text( FL_ALIGN_CENTER, ob->x, ob->y, ob->w, ob->h,
                     ob->lcol, ob->lstyle, ob->lsize, str );
    }
}
