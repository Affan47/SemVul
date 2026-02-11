insertobj(qlisttbl_t *tbl, qlisttbl_obj_t *obj)
{

    obj->hash = qhashmurmur3_32(obj->name, strlen(obj->name));

    qlisttbl_obj_t *prev = obj->prev;
    qlisttbl_obj_t *next = obj->next;

    if (prev == NULL) tbl->first = obj;
    else prev->next = obj;

    if (next == NULL) tbl->last = obj;
    else next->prev = obj;


    tbl->num++;

    return true;
}
