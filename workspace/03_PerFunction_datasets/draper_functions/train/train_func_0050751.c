val_int()
{
  DBUG_ASSERT(fixed == 1);
  if (aggr)
    aggr->endup();
  return (longlong) count;
}
