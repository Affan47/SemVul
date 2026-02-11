freeStack(stack *s, void (*destructor)(void *e))
{
  void *e;
  if (destructor)
    while ((e = pop(s)))
      destructor(e);

  free(s->arr);
  free(s);
}
