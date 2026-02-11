cl_delete_tab(struct clause *c)
{
  struct clause_ptr *cp1, *cp2;
  int hashval, id;

  id = c->id;
  hashval = id % CLAUSE_TAB_SIZE;
  cp1 = Clause_tab[hashval];
  cp2 = NULL;


  while (cp1 && cp1->c->id < id) {
    cp2 = cp1;
    cp1 = cp1->next;
  }
  if (!cp1 || cp1->c->id != id) {
    print_clause(stdout, c);
    abend("cl_delete_tab, clause not found.");
  }
  else {
    if (!cp2)
      Clause_tab[hashval] = cp1->next;
    else
      cp2->next = cp1->next;
    free_clause_ptr(cp1);
  }
}
