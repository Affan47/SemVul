DGG_isCutDesirable(DGG_constraint_t *c, DGG_data_t *d)
{
  double lhs, rhs;

  lhs = DGG_cutLHS(c, d->x);
  rhs = c->rhs;

  if (c->nz > 500) return 0;


  if (c->sense == 'G')
    if ( lhs > (rhs - DGG_NULL_SLACK) )
      return 0;
  if (c->sense == 'L')
    if ( lhs < (rhs + DGG_NULL_SLACK) )
      return 0;
  if (c->sense == 'E')
    if ( fabs(lhs - rhs) < DGG_NULL_SLACK )
      return 0;
  return 1;
}
