biv_total_increment (bl)
     const struct iv_class *bl;
{
  struct induction *v;
  rtx result;


  result = const0_rtx;
  for (v = bl->biv; v; v = v->next_iv)
    {
      if (v->always_computable && v->mult_val == const1_rtx
	  && ! v->maybe_multiple
	  && SCALAR_INT_MODE_P (v->mode))
	{

	  if (v->same)
	    continue;

	  result = fold_rtx_mult_add (result, const1_rtx, v->add_val, v->mode);
	}
      else
	return 0;
    }

  return result;
}
