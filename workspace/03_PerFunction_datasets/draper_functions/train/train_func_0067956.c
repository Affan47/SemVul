SetCoefficient(double coeff, int index)
{
  if (index < 0 || index > GD_MAX_POLYORD)
    return -1;

  E.u.polynom.ca[index][0] = E.u.polynom.a[index] = coeff;
  E.u.polynom.ca[index][1] = 0;

  if (D != NULL)
    return gd_alter_entry(D->D, E.field, &E, 0);

  return 0;
}
