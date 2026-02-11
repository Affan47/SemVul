plist_remove_string(Plist p, char *s)
{
  if (p == NULL)
    fatal_error("plist_remove_string: pointer not found");

  if (str_ident(p->v, s)) {
    Plist x = p;
    p = p->next;
    free_plist(x);
    return p;
  }
  else {
    p->next = plist_remove_string(p->next, s);
    return p;
  }
}
