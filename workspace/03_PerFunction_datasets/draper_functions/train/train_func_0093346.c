nth_clause(struct clause_ptr *p, int n)
{
  if (p == NULL)
    return NULL;
  else if (n == 1)
    return p->c;
  else
    return nth_clause(p->next, n-1);
}
