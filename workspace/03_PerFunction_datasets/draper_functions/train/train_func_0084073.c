fs_list_insert_before(fs_list *list, fs_list *sibling, void * data) {
    if (!list) {
        list = fs_list_alloc();
        list->data = data;

        if (sibling != NULL) {
            return list;
        }
        return list;
    }
    else if (sibling) {
        fs_list *node;

        node = _fs_list_alloc();
        node->data = data;
        node->prev = sibling->prev;
        node->next = sibling;
        sibling->prev = node;
        if (node->prev) {
            node->prev->next = node;
            return list;
        }
        else {

            if (sibling != list) {
                return node;
            }
            return node;
        }
    }
    else {
        fs_list *last;

        last = list;
        while (last->next)
            last = last->next;

        last->next = _fs_list_alloc();
        last->next->data = data;
        last->next->prev = last;
        last->next->next = NULL;

        return list;
    }
}
