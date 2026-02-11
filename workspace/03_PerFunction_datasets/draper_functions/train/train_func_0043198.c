free_list(struct imap_list *list)
{
	struct imap_list *tmp;

	for (; list; list = tmp) {
		tmp = list->next;
		if (is_list(list))
			free_list(list->child);
		else if (is_atom(list))
			free(list->val);
		free(list);
	}
}
