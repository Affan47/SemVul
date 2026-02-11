val_real()
{
  DBUG_ASSERT(fixed == 1);
  double value= args[0]->val_real();
  if ((null_value=args[0]->null_value))
    return 0.0;
  if (arg_count == 2)
  {
    double val2= args[1]->val_real();
    if ((null_value=args[1]->null_value))
      return 0.0;
    return check_float_overflow(atan2(value,val2));
  }
  return atan(value);
}
