dict_remove(Dict *dict, Octstr *key)
{
    long i;
    Item *p;
    void *value;
    List *list;

    lock(dict);
    i = key_to_index(dict, key);
    if (dict->tab[i] == NULL)
        list = NULL;
    else
        list = gwlist_extract_matching(dict->tab[i], key, item_has_key);
    gw_assert(list == NULL || gwlist_len(list) == 1);
    if (list == NULL)
    	value = NULL;
    else {
	p = gwlist_get(list, 0);
	gwlist_destroy(list, NULL);
    	value = p->value;
	item_destroy(p);
	dict->key_count--;
    }
    unlock(dict);
    return value;
}
