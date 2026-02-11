llist_insert_sorted_unique(struct llist *list,
			const unsigned char *sha1, struct llist_item *hint)
{
	struct llist_item *prev = NULL, *l;

	l = (hint == NULL) ? list->front : hint;
	while (l) {
		int cmp = hashcmp(l->sha1, sha1);
		if (cmp > 0) {
			return llist_insert(list, prev, sha1);
		}
		if (!cmp) {
			return l;
		}
		prev = l;
		l = l->next;
	}

	return llist_insert_back(list, sha1);
}
