j_subsumed_recurse(int *s, struct ilist *p)
{
  if (p == NULL) {
#if DEBUG
    printf("         Checking hash membership: "); print_set(s); printf("\n");
#endif
    return jhash_member(s);
  }
#if 0
  else if (j_subsumed_recurse(s, p->next))
    return 1;
  else {
    int subsumed;
    add_to_jset(s, p->i);
    subsumed = j_subsumed_recurse(s, p->next);
    remove_from_jset(s, p->i);
    return subsumed;
  }
#else
  else {
    int subsumed;
    add_to_jset(s, p->i);
    subsumed = j_subsumed_recurse(s, p->next);
    remove_from_jset(s, p->i);
    if (subsumed)
      return 1;
    else if (j_subsumed_recurse(s, p->next))
      return 1;
    else
      return 0;
  }
#endif
}
