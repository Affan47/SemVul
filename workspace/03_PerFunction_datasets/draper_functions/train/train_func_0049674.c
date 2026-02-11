dump_recorded_exit (void **slot, void *file)
{
  struct loop_exit *exit = (struct loop_exit *) *slot;
  unsigned n = 0;
  edge e = exit->e;

  for (; exit != NULL; exit = exit->next_e)
    n++;

  fprintf ((FILE*) file, "Edge %d->%d exits %u loops\n",
	   e->src->index, e->dest->index, n);

  return 1;
}
