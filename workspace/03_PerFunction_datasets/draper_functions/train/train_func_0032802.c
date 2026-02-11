REMOVE_ELEM(LINK_ELEMENT *elem)
{
    elem->prev->next = elem->next;
    if (elem->next) {
	elem->next->prev = elem->prev;
    }
}
