fs_list_append(fs_list *list, void * data) {
    fs_list *new_list;
    fs_list *last;

    new_list = _fs_list_alloc();
    new_list->data = data;
    new_list->next = NULL;

    if (list) {
        last = fs_list_last(list);

        last->next = new_list;
        new_list->prev = last;

        return list;
    }
    else {
        new_list->prev = NULL;
        return new_list;
    }
}
