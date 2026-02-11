list_append(list_t *list, void *data)
{
    elem_t *elem = NULL;

    if (list) {
        elem = elem_construct(data);
        if (elem) {
            if (list->cnt == 0) {
                list->first = list->last = elem;
            } else {
                list->last->next = elem;
                elem->prev = list->last;
                list->last = elem;
            }
            list->cnt++;
        }
    }
    return elem;
}
