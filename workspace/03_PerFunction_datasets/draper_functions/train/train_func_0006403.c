sub_clause(struct clause *c1,
	       struct clause *c2)
{
  struct literal *l1, *l2;
  int found;

  for(l1 = c1->first_lit; l1; l1 = l1->next_lit) {
    l2 = c2->first_lit;
    found = 0;
    while (l2 && !found) {
      if (l1->sign == l2->sign && l1->atom->sym_num == l2->atom->sym_num)
	found = 1;
      else
	l2 = l2->next_lit;
    }
    if (!found)
      return(0);
  }
  return(1);
}
