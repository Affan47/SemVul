next_msection
   ___P((msection *ms),
        (ms)
msection *ms;)
{
  msection *result;

  if (nb_msections_used == 0)
    result = the_msections->head;
  else
    result = alloc_msection->next;

  if (result == 0)
    {
      if (stack_msection == heap_msection)
        fatal_heap_overflow ();
      result = ms;
    }
  else
    {
      alloc_msection = result;
      nb_msections_used++;
    }

  return result;
}
