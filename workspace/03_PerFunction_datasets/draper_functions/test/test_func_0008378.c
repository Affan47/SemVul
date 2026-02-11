gwlist_destroy(List *list, gwlist_item_destructor_t *destructor)
{
    long len, i;

    if (list == NULL)
        return;

    if (destructor != NULL) {
        len = gwlist_len(list);
        for (i = 0; i < len; i++)
          destructor(gwlist_extract_first(list));
    }

    mutex_destroy(list->permanent_lock);
    mutex_destroy(list->single_operation_lock);
    pthread_cond_destroy(&list->nonempty);
    gw_free(list->tab);
    gw_free(list);
}
