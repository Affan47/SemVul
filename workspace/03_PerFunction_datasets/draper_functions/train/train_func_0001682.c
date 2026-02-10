fs_list_remove_all(fs_list *list, const void * data) {
    fs_list *tmp = list;

    while (tmp) {
        if (tmp->data != data) tmp = tmp->next;
        else {
            fs_list *next = tmp->next;

            if (tmp->prev) tmp->prev->next = next;
            else list = next;
            if (next) next->prev = tmp->prev;

            fs_list_free_1(tmp);
            tmp = next;
        }
    }
    return list;
}
