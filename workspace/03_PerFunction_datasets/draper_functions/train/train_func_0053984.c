collect_lookups (unsigned int table_index, hb_set_t *lookups_out) const
{
  for (unsigned int i = 0; i < lookups[table_index].len; i++)
    hb_set_add (lookups_out, lookups[table_index][i].index);
}
