get_contacts(chat_window *cw)
{
        LList *node = groups;
	while (node) {
		get_group_contacts(node->data, cw);
		node = node->next;
	}
}
