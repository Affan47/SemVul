test_for_current_value (space, ndim)
     struct dimension *space;
     int ndim;
{
  int i;
  rtx exp = true_rtx;

  for (i = 0; i < ndim; i++)
    exp = insert_right_side (AND, exp, XEXP (space[i].current_value, 0),
			     -2, -2);

  return exp;
}
