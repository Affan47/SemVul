fl_get_choice_item_text( FL_OBJECT * ob,
                         int         n )
{
    FLI_CHOICE_SPEC *sp = ob->spec;

    if ( n < 1 || n > sp->numitems )
        return NULL;

    return sp->items[ n ];
}
