kill_assoc(int chan)
{
  assoc_t *a = assoc, *last = NULL;

  while (a) {
    if (a->channel == chan) {
      if (last != NULL)
        last->next = a->next;
      else
        assoc = a->next;
      nfree(a);
      a = NULL;
    } else {
      last = a;
      a = a->next;
    }
  }
}
