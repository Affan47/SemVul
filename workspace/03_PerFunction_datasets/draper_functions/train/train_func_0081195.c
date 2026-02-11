hlist_add(hlist_t list, char *key, char *value, hlist_add_t allockey, hlist_add_t allocvalue) {
	hlist_t tmp, t = list;

	if (key == NULL || value == NULL)
		return list;

	tmp = malloc(sizeof(struct hlist_s));
	tmp->key = (allockey == HLIST_ALLOC ? strdup(key) : key);
	tmp->value = (allocvalue == HLIST_ALLOC ? strdup(value) : value);
	tmp->next = NULL;
	tmp->islist = 0;

	if (list == NULL)
		return tmp;

	while (t->next)
		t = t->next;

	t->next = tmp;

	return list;
}
