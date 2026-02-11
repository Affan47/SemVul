sw_set_union (SwSet *set_a,
              SwSet *set_b)
{
  SwSet *set;

  g_return_val_if_fail (set_a, NULL);
  g_return_val_if_fail (set_b, NULL);

  set = sw_set_new ();

  g_hash_table_foreach (set_a->hash, add_to_set, set);
  g_hash_table_foreach (set_b->hash, add_to_set, set);

  return set;
}
