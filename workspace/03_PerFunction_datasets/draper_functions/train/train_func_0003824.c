s48_bignum_to_digit_stream(bignum_type bignum,
			   unsigned int radix,
			   void (*consumer)(bignum_procedure_context,
					    bignum_digit_type),
			   bignum_procedure_context context)
{
  BIGNUM_ASSERT ((radix > 1) && (radix <= BIGNUM_RADIX_ROOT));
  if (! (BIGNUM_ZERO_P (bignum)))
    {
      bignum_type working_copy = (bignum_copy (bignum));
      bignum_digit_type * start = (BIGNUM_START_PTR (working_copy));
      bignum_digit_type * scan = (start + (BIGNUM_LENGTH (working_copy)));
      while (start < scan)
	{
	  if ((scan[-1]) == 0)
	    scan -= 1;
	  else
	    (*consumer)
	      (context, (bignum_destructive_scale_down (working_copy, radix)));
	}
      BIGNUM_DEALLOCATE (working_copy);
    }
  return;
}
