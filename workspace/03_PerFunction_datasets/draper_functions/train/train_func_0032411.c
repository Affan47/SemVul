list_append_list(struct linked_list* list, struct linked_list* other)
{

	if (!other->size)
		return;

	if (!list->size)
	{

		list->size = other->size;
		list->first = other->first;
		list->last = other->last;
		list->iterator = other->iterator;
	}
	else
	{
		other->first->prev = list->last;
		list->last->next = other->first;
		list->last = other->last;
		list->size += other->size;
	}


	other->size = 0;
	other->first = NULL;
	other->last = NULL;
	other->iterator = NULL;
}
