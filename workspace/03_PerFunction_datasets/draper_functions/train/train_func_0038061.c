zend_stack_apply_with_argument(zend_stack *stack, int type, int (*apply_function)(void *element, void *arg), void *arg)
{
	int i;

	switch (type) {
		case ZEND_STACK_APPLY_TOPDOWN:
			for (i=stack->top-1; i>=0; i--) {
				if (apply_function(stack->elements[i], arg)) {
					break;
				}
			}
			break;
		case ZEND_STACK_APPLY_BOTTOMUP:
			for (i=0; i<stack->top; i++) {
				if (apply_function(stack->elements[i], arg)) {
					break;
				}
			}
			break;
	}
}
