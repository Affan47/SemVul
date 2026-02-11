find_clause_by_id(int id)
{
  int i;
  Plist p1;

  i = id % CLAUSE_ID_TAB_SIZE;
  for (p1 = Topform_id_tab[i];
       p1 && ((Topform) p1->v)->id < id;
       p1 = p1->next);
  if (p1 != NULL && ((Topform) p1->v)->id == id)
    return(p1->v);
  else
    return(NULL);
}
