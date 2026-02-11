fli_insert_composite_after( FL_OBJECT * obj,
                            FL_OBJECT * after )
{
    FL_OBJECT *next,
              *tmp,
              *prev;
    FL_FORM *form;

    if ( ! obj || ! after )
    {
        M_err( "fli_insert_composite_after", "Bad argument" );
        return;
    }

    if ( ! ( form = after->form ) )
    {
        M_err( "fli_insert_composite_after", "Null form" );
        return;
    }

    obj->form = form;

    next            = after->next;
    after->next     = obj;
    obj->prev       = after;
    obj->next       = obj->child;
    obj->next->prev = obj;
    prev            = obj;

    for ( tmp = obj->child; tmp->nc; prev = tmp, tmp = tmp->nc )
    {
        tmp->parent = obj;
        tmp->form   = form;
        tmp->next   = tmp->nc;
        tmp->prev   = prev;
    }

    tmp->next = next;
    tmp->prev = prev;
    tmp->form = form;

    if ( form->last == after )
        form->last = tmp;
}
