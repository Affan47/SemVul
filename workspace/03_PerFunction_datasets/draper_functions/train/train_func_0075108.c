fs_list_prepend(fs_list *list, void *data) {
    fs_list *new_list;

    new_list = _fs_list_alloc();
    new_list->data = data;
    new_list->next = list;

    if (list) {
        new_list->prev = list->prev;
        if (list->prev) list->prev->next = new_list;
        list->prev = new_list;
    }
    else new_list->prev = NULL;

    return new_list;
}
