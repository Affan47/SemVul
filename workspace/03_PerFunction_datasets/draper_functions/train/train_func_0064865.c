MatrixStackSetStackPosition (MatrixStack *stack, int pos)
{
	stack->position += pos;

	if (stack->position < 0)
		stack->position = 0;
	else if (stack->position > stack->size)
		stack->position = stack->size;
}
