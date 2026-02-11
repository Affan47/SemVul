allocno_cost_compare_func (const void *v1p, const void *v2p)
{
  ira_allocno_t p1 = *(const ira_allocno_t *) v1p;
  ira_allocno_t p2 = *(const ira_allocno_t *) v2p;
  int c1, c2;

  c1 = ALLOCNO_UPDATED_MEMORY_COST (p1) - ALLOCNO_UPDATED_CLASS_COST (p1);
  c2 = ALLOCNO_UPDATED_MEMORY_COST (p2) - ALLOCNO_UPDATED_CLASS_COST (p2);
  if (c1 - c2)
    return c1 - c2;


  return ALLOCNO_NUM (p1) - ALLOCNO_NUM (p2);
}
