flps_draw_timer( FL_OBJECT * ob )
{
    char *str;
    SPEC *sp = ob->spec;

    if ( ob->type == FL_HIDDEN_TIMER )
        return;

    ps_draw_box( ob->boxtype, ob->x, ob->y, ob->w, ob->h, ob->col1, ob->bw );

    if ( ob->type == FL_VALUE_TIMER )
    {
        str = default_filter( ob, sp->val == 0.0 ? 100.0 : sp->val );
        ps_draw_text( FL_ALIGN_CENTER, ob->x, ob->y, ob->w, ob->h,
                      ob->lcol, ob->lstyle, ob->lsize, str );
        ob->align &= ~FL_ALIGN_INSIDE;
        if ( ob->align == FL_ALIGN_CENTER )
            ob->align = FL_ALIGN_LEFT;
    }

    ps_draw_object_label( ob );
}
