free_pattern_chain(patstr *pc)
{
while (pc != NULL)
  {
  patstr *p = pc;
  pc = p->next;
  if (p->hint != NULL) pcre_free_study(p->hint);
  if (p->compiled != NULL) pcre_free(p->compiled);
  free(p);
  }
}
