set_need_recalc( FL_POPUP * popup )
{
    FL_POPUP_ENTRY *e;

    popup->need_recalc = 1;

    for ( e = popup->entries; e != NULL; e = e->next )
        if ( e->type == FL_POPUP_SUB )
            set_need_recalc( e->sub );
}
