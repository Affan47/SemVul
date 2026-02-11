proof_id_to_clause(Plist proof, int id)
{
  Plist p = proof;
  while (p && ((Topform) p->v)->id != id)
    p = p->next;
  if (p == NULL)
    return NULL;
  else
    return p->v;
}
