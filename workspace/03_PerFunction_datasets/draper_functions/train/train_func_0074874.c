af_nrofkeys (set)
     Af_set *set;
{
  if (af_settest (set))
    FAIL ("nrofkeys", "", AF_EINVSET, ERROR);
  return (set->af_nkeys);
}
