list_append(list_t *list, void *data)
{
	link_t *link;

	if ((link = calloc(1, sizeof(link_t))) == NULL) {
		fprintf(stderr, "Cannot allocate list link.\n");
		return NULL;
	}
	link->data = data;
	if (list->head == NULL) {
		list->head = link;
	} else {
		list->tail->next = link;
	}
	list->tail = link;
	list->length++;

	return link;
}
