remove_sl(
    am_sl_t *	sl,
    sle_t *	elem)
{
    if(elem->prev)
	elem->prev->next = elem->next;
    else
	sl->first = elem->next;

    if(elem->next)
	elem->next->prev = elem->prev;
    else
	sl->last = elem->prev;

    sl->nb_element--;

    amfree(elem->name);
    amfree(elem);
}
