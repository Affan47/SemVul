DGG_isConstraintViolated(DGG_data_t *d, DGG_constraint_t *c)
{
  double lhs = DGG_cutLHS(c, d->x);
  double rhs = c->rhs;


  if (c->sense == 'G')
    if ( lhs > (rhs - DGG_NULL_SLACK) )
      return 0;
  if (c->sense == 'L')
    if ( lhs < (rhs + DGG_NULL_SLACK) )
      return 0;
  if (c->sense == 'E')
    if ( fabs(lhs - rhs) < DGG_NULL_SLACK )
      return 0;

  return 0;

}
