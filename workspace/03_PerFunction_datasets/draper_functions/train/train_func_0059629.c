grecs_list_add(struct grecs_list *dst, struct grecs_list *src)
{
	if (!src->head)
		return;

	src->head->prev = dst->tail;
	if (dst->tail)
		dst->tail->next = src->head;
	else
		dst->head = src->head;
	dst->tail = src->tail;
	dst->count += src->count;
	src->head = src->tail = NULL;
	src->count = 0;
}
