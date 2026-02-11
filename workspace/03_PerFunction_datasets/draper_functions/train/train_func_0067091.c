slset_destroy_set(struct slset *s, bool d_data, void (*deallocator)(void *))
{
	struct slset_entry *tmp;
	struct slset_entry *i = s->first;

	while (i != NULL) {
		tmp = i;
		i = i->next;
		if (d_data) {
			deallocator(tmp->data);
		}
		deallocator(tmp);
	}
}
