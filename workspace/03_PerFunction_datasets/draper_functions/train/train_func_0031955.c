inc_attr_count(struct attr_counter **top, struct attr_counter *ac,
    struct attr_counter *last, struct mtree_entry *me)
{
	struct attr_counter *pac;

	if (ac != NULL) {
		ac->count++;
		if (*top == ac || ac->prev->count >= ac->count)
			return (0);
		for (pac = ac->prev; pac; pac = pac->prev) {
			if (pac->count >= ac->count)
				break;
		}
		ac->prev->next = ac->next;
		if (ac->next != NULL)
			ac->next->prev = ac->prev;
		if (pac != NULL) {
			ac->prev = pac;
			ac->next = pac->next;
			pac->next = ac;
			if (ac->next != NULL)
				ac->next->prev = ac;
		} else {
			ac->prev = NULL;
			ac->next = *top;
			*top = ac;
			ac->next->prev = ac;
		}
	} else {
		ac = new_attr_count(me, last);
		if (ac == NULL)
			return (-1);
		last->next = ac;
	}
	return (0);
}
