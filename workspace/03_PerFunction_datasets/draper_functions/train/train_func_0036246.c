paircompare_unregister(unsigned int attribute, RAD_COMPARE_FUNC func)
{
	struct cmp *c, *last;

	last = NULL;
	for (c = cmp; c; c = c->next) {
		if (c->attribute == attribute && c->compare == func) {
			break;
		}
		last = c;
	}

	if (c == NULL) return;

	if (last != NULL) {
		last->next = c->next;
	} else {
		cmp = c->next;
	}

	free(c);
}
