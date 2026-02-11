general_stack_push_fr(struct general_stack *stack, void *data)
{
	if (general_stack_full_fr(stack))
	{
		return -ENOMEM;
	}

	stack->buffer[++(stack->top)] = data;

	return 0;
}
