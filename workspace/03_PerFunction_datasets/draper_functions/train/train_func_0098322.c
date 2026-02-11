print_stack(stack)
STACK *stack;
{
   printf("Stack: ");
   if (stack_empty(stack))
      printf("(empty)\n");
   else {
      list_traverse(stack, (char *) 0, print_element,
		    (LIST_FRNT | LIST_FORW | LIST_SAVE));
      printf("\n");
   }
}
