free_curl_slist(struct curl_slist *slist)
{
    struct curl_slist *item;

    if (slist == NULL)
        return;

    item = slist;

    while (item != NULL)
    {
        free(item->data);
        item->data = NULL;
        item = item->next;
    }

    curl_slist_free_all(slist);
}
