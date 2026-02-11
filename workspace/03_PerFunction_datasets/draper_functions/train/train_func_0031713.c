get_all_contacts()
{
	LList *node = get_groups();
	LList *newlist = NULL;

	while (node) {
		LList *g = get_contacts(node->data);
		newlist = l_list_concat(newlist, g);
		node = node->next;
	}

	return newlist;
}
