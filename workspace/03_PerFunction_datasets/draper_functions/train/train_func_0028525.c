b_slist_free_full(b_slist_t *l, b_free_func_t free_func)
{
    while (l != NULL) {
        b_slist_t *tmp = l->next;
        free_func(l->data);
        free(l);
        l = tmp;
    }
}
