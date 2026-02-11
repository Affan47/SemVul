modperl_list_prepend(modperl_list_t *list,
                                     modperl_list_t *new_list)
{
    new_list->prev = new_list->next = NULL;

    if (!list) {
        return new_list;
    }

    if (list->prev) {
        list->prev->next = new_list;
        new_list->prev = list->prev;
    }

    list->prev = new_list;
    new_list->next = list;

    return new_list;
}
