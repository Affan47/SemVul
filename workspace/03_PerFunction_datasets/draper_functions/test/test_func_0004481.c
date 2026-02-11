qhashtbl_clear(qhashtbl_t *tbl) {
    qhashtbl_lock(tbl);
    int idx;
    for (idx = 0; idx < tbl->range && tbl->num > 0; idx++) {
        if (tbl->slots[idx] == NULL)
            continue;
        qhashtbl_obj_t *obj = tbl->slots[idx];
        tbl->slots[idx] = NULL;
        while (obj != NULL) {
            qhashtbl_obj_t *next = obj->next;
            free(obj->name);
            free(obj->data);
            free(obj);
            obj = next;

            tbl->num--;
        }
    }

    qhashtbl_unlock(tbl);
}
