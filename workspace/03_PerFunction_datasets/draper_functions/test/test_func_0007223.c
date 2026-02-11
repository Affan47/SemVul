zap_plist_of_terms(Plist lst)
{
  Plist p = lst;
  while (p != NULL) {
    Plist p2 = p;
    p = p->next;
    zap_term(p2->v);
    free_plist(p2);
  }
}
