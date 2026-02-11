l_list_append(LList *list, void *data)
{
	LList *n;
	LList *new_list = malloc(sizeof(LList));
	LList *attach_to = NULL;

	new_list->next = NULL;
	new_list->data = data;

	for (n = list; n != NULL; n = n->next) {
		attach_to = n;
	}

	if (attach_to == NULL) {
		new_list->prev = NULL;
		return new_list;
	} else {
		new_list->prev = attach_to;
		attach_to->next = new_list;
		return list;
	}
}
