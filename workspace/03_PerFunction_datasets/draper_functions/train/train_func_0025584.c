push_symbol_table(struct symbol_table * table,
				       gp_boolean case_insensitive)
{
  struct symbol_table *new = calloc(sizeof(*new), 1);

  new->case_insensitive = case_insensitive;
  if (case_insensitive)
    new->compare = strcasecmp;
  else
    new->compare = strcmp;
  new->prev = table;
  return new;
}
