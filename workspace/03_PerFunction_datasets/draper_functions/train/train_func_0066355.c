copy_filestruct(const filestruct *src)
{
    filestruct *head, *copy;

    assert(src != NULL);

    copy = copy_node(src);
    copy->prev = NULL;
    head = copy;
    src = src->next;

    while (src != NULL) {
	copy->next = copy_node(src);
	copy->next->prev = copy;
	copy = copy->next;

	src = src->next;
    }

    copy->next = NULL;

    return head;
}
