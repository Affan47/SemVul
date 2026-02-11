Full_Coeff_Power_Var(Range *y, int a, Range *n)
{
  unsigned an, an0;
  int i, vec_elem;

  an = Power(a, n->min);

  Vector_Allocate(y->vec);
  if (an > (unsigned) vec_max_integer)
    {
      y->extra_cstr = TRUE;
      Set_To_Empty(y);
      return;
    }

  Vector_Empty(y->vec);
  y->extra_cstr = FALSE;
  y->min = an;

  if (Is_Interval(n))
    {
      an0 = an;
      for (i = n->min; i <= n->max; i++)
	{
	  if (an0 > (unsigned) vec_max_integer)
	    goto end_loop;

	  an = an0;
	  Vector_Set_Value(y->vec, an);
	  an0 *= a;
	}
    }
  else
    {
      y->extra_cstr = n->extra_cstr;

      VECTOR_BEGIN_ENUM(n->vec, vec_elem);

      an = Power(a, vec_elem);
      if (an > (unsigned) vec_max_integer)
	goto end_loop;

      Vector_Set_Value(y->vec, an);

      VECTOR_END_ENUM;
    }
end_loop:

  y->max = an;
}
