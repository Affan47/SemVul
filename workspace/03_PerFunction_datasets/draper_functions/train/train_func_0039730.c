ctpl_stack_pop (CtplStack *stack)
{
  gpointer data = NULL;

  if (stack->head) {
    GSList *next = stack->head->next;

    data = stack->head->data;
    g_slist_free_1 (stack->head);
    stack->head = next;
  }

  return data;
}
