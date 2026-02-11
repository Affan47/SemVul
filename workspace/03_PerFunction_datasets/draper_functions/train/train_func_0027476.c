commit_list_pop(commit_list **stack)
{
	commit_list *top = *stack;
	commit_object *item = top ? top->item : NULL;

	if (top) {
		*stack = top->next;
		free(top);
	}
	return item;
}
