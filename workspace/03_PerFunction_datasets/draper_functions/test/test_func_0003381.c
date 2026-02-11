send_ancestors(struct commit *commit, int round)
{
	struct commit_list *list = NULL;
	struct commit_list **tail = &list;
	int count = 0;

	tail = &commit_list_insert(commit, tail)->next;
	while (list && count < BATCH) {
		struct commit_list *elem = list;
		struct commit *c = elem->item;

		list = list->next;
		free(elem);
		if (!list)
			tail = &list;

		if (c->object.flags & SHOWN_TO_SENDER)
			continue;
		if (parse_commit(c))
			continue;
		c->object.flags |= SHOWN_TO_SENDER;
		if (c != commit) {
			packet_write(1, "%s %s\n",
				     sha1_to_hex(c->object.sha1),
				     sha1_to_hex(commit->object.sha1));
			count++;
		}
		tail = add_parents(c, tail, round);
	}
	clear_commit_marks(commit, SHOWN_TO_SENDER);
	free_commit_list(list);
}
