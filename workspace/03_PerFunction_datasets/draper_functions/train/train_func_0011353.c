ins_dlnode(DLLIST * list, DLNODE * node, APTR data) {
    DLNODE *newnode = NULL;

    if (list) {
        newnode = new_dlnode();

        if (newnode) {
            newnode->data = data;
            list->entry_num++;

            if (node) {
                if (dll_first(list) == node) {

                    list->first = newnode;
                } else {

                    dln_next(dln_prev(node)) = newnode;
                    dln_prev(newnode) = node->prev;
                }
                dln_prev(node) = newnode;
                dln_next(newnode) = node;
            } else {
                if (dll_last(list))
                    list->last->next = newnode;
                dln_prev(newnode) = dll_last(list);
                dll_last(list) = newnode;
            }

            if (dll_first(list) == NULL)
                dll_first(list) = newnode;
            if (dll_last(list) == NULL)
                dll_last(list) = newnode;
        }
    }
    return newnode;
}
