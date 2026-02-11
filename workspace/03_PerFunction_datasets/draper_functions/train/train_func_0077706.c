verify_bintree(dict_t *dict)
{
    dnode_t *first, *next;

    first = dict_first(dict);

    if (dict->dupes) {
	while (first && (next = dict_next(dict, first))) {
	    if (dict->compare(first->key, next->key) > 0)
		return 0;
	    first = next;
	}
    } else {
	while (first && (next = dict_next(dict, first))) {
	    if (dict->compare(first->key, next->key) >= 0)
		return 0;
	    first = next;
	}
    }
    return 1;
}
