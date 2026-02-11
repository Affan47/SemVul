qlist_reverse(qlist_t *list) {
    qlist_lock(list);
    qlist_obj_t *obj;
    for (obj = list->first; obj;) {
        qlist_obj_t *next = obj->next;
        obj->next = obj->prev;
        obj->prev = next;
        obj = next;
    }

    obj = list->first;
    list->first = list->last;
    list->last = obj;

    qlist_unlock(list);
}
