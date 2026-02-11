Range_Set_Value(Range *range, int n)
{
  if (Is_Empty(range))
    {
      Range_Init_Interval(range, n, n);
      return;
    }

  if (Is_Interval(range))
    {
      if (n >= range->min && n <= range->max)
	return;

      if (n == range->min - 1)
	{
	  range->min--;
	  return;
	}

      if (n == range->max + 1)
	{
	  range->max++;
	  return;
	}

      Range_Becomes_Sparse(range);
      if ((unsigned) n <= (unsigned) vec_max_integer)
	{
	  Vector_Set_Value(range->vec, n);
	  Range_From_Vector(range);
	}
      else
	range->extra_cstr = TRUE;

      return;
    }

  if ((unsigned) n > (unsigned) vec_max_integer)
    {
      range->extra_cstr = TRUE;
      return;
    }

  Vector_Set_Value(range->vec, n);
  if (n < range->min || n > range->max)
    Range_From_Vector(range);
}
