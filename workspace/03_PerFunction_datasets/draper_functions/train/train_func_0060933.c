plist_mark_all_unchecked(conf_llist* l)
{
	register lnode* current;

	current = l->head;
	while (current) {
		if (current->p)
			current->p->checked = 0;
		current=current->next;
	}
}
