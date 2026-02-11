sort_lits(struct clause *c)
{
  struct literal *sorted, *prev, *curr, *next, *insert;
  int changed = 0;


  if (c->first_lit) {
    sorted = c->first_lit;
    insert = sorted->next_lit;
    sorted->next_lit = NULL;

    while(insert) {
      prev = NULL;
      curr = sorted;
      while (curr && lit_compare(insert, curr) == GREATER_THAN) {
	prev = curr;
	curr = curr->next_lit;
      }
      if (curr != NULL)
	changed = 1;
      next = insert->next_lit;
      insert->next_lit = curr;
      if (prev)
	prev->next_lit = insert;
      else
	sorted = insert;
      insert = next;
    }
    c->first_lit = sorted;
  }
  return changed;
}
