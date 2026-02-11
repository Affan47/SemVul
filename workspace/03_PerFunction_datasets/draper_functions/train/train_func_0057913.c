hash_die (struct hash_control *table)
{
  obstack_free (&table->memory, 0);
  free (table);
}
