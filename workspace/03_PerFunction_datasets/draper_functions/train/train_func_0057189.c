delay_free_mem()
{
  struct delay_mode *d = NULL, *dnext = NULL;

  for (d = delay_head; d; d = dnext) {
    dnext = d->next;

    if (d->mask)
      nfree(d->mask);

    nfree(d);
  }

  delay_head = NULL;
  delay_tail = NULL;
}
