gwlist_extract_first(List *list)
{
    void *item;

    gw_assert(list != NULL);
    lock(list);
    if (list->len == 0)
        item = NULL;
    else {
        item = GET(list, 0);
        delete_items_from_list(list, 0, 1);
    }
    unlock(list);
    return item;
}
