fl_set_timer_filter( FL_OBJECT *     ob,
                     FL_TIMER_FILTER filter )
{
    SPEC *sp = ob->spec;
    FL_TIMER_FILTER old = sp->filter;

    if ( filter != sp->filter )
    {
        sp->filter = filter;
        fl_redraw_object( ob );
    }
    return old;
}
