object_range_compare_func (const void *v1p, const void *v2p)
{
  int diff;
  ira_object_t obj1 = *(const ira_object_t *) v1p;
  ira_object_t obj2 = *(const ira_object_t *) v2p;
  ira_allocno_t a1 = OBJECT_ALLOCNO (obj1);
  ira_allocno_t a2 = OBJECT_ALLOCNO (obj2);

  if (flag_ira_algorithm != IRA_ALGORITHM_PRIORITY
      && (diff = ALLOCNO_COVER_CLASS (a1) - ALLOCNO_COVER_CLASS (a2)) != 0)
    return diff;
  if ((diff = OBJECT_MIN (obj1) - OBJECT_MIN (obj2)) != 0)
    return diff;
  if ((diff = OBJECT_MAX (obj1) - OBJECT_MAX (obj2)) != 0)
     return diff;
  return ALLOCNO_NUM (a1) - ALLOCNO_NUM (a2);
}
