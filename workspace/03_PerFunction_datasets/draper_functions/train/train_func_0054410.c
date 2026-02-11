dump_pair_list (const char *name, pair_p pp)
{
  pair_p p;
  printf ("%s:\n", name);
  for (p = pp; p != NULL; p = p->next)
    dump_pair (0, p);
  printf ("End of %s\n\n", name);
}
