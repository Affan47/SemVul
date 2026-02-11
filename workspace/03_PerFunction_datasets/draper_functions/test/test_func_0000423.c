lower_bound_in_type (tree outer, tree inner)
{
  unsigned HOST_WIDE_INT lo, hi;
  unsigned oprec = TYPE_PRECISION (outer);
  unsigned iprec = TYPE_PRECISION (inner);


  if (TYPE_UNSIGNED (outer)


      || (oprec > iprec && TYPE_UNSIGNED (inner)))
    lo = hi = 0;
  else
    {


      unsigned prec = oprec > iprec ? iprec : oprec;

      if (prec <= HOST_BITS_PER_WIDE_INT)
	{
	  hi = ~(unsigned HOST_WIDE_INT) 0;
	  lo = (~(unsigned HOST_WIDE_INT) 0) << (prec - 1);
	}
      else
	{
	  hi = ((~(unsigned HOST_WIDE_INT) 0)
		<< (prec - HOST_BITS_PER_WIDE_INT - 1));
	  lo = 0;
	}
    }

  return build_int_cst_wide (outer, lo, hi);
}
