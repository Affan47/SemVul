prot_freq_compare (gconstpointer a, gconstpointer b)
{
  const protocol_t *prot_a, *prot_b;

  g_assert (a != NULL);
  g_assert (b != NULL);

  prot_a = (const protocol_t *) a;
  prot_b = (const protocol_t *) b;

  if (prot_a->stats.accumulated > prot_b->stats.accumulated)
    return -1;
  if (prot_a->stats.accumulated < prot_b->stats.accumulated)
    return 1;
  return 0;
}
