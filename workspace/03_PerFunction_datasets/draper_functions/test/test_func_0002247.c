general_stack_pop_fd(struct general_stack *stack)
{
	if (general_stack_empty_fd(stack))
	{
		return NULL;
	}

	return stack->buffer[(stack->top)++];
}
