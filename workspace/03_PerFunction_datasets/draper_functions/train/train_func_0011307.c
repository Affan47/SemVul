flonum_multip (const FLONUM_TYPE *a, const FLONUM_TYPE *b,
	       FLONUM_TYPE *product)
{
  int size_of_a;
  int size_of_b;
  int size_of_product;
  int size_of_sum;
  int extra_product_positions;
  unsigned long work;
  unsigned long carry;
  long exponent;
  LITTLENUM_TYPE *q;
  long significant;

  int P;
  int N;
  int A;
  int B;

  if ((a->sign != '-' && a->sign != '+')
      || (b->sign != '-' && b->sign != '+'))
    {

      product->sign = 0;
      return;
    }
  product->sign = (a->sign == b->sign) ? '+' : '-';
  size_of_a = a->leader - a->low;
  size_of_b = b->leader - b->low;
  exponent = a->exponent + b->exponent;
  size_of_product = product->high - product->low;
  size_of_sum = size_of_a + size_of_b;
  extra_product_positions = size_of_product - size_of_sum;
  if (extra_product_positions < 0)
    {
      P = extra_product_positions;
      exponent -= extra_product_positions;
    }
  else
    {
      P = 0;
    }
  carry = 0;
  significant = 0;
  for (N = 0; N <= size_of_sum; N++)
    {
      work = carry;
      carry = 0;
      for (A = 0; A <= N; A++)
	{
	  B = N - A;
	  if (A <= size_of_a && B <= size_of_b && B >= 0)
	    {
#ifdef TRACE
	      printf ("a:low[%d.]=%04x b:low[%d.]=%04x work_before=%08x\n",
		      A, a->low[A], B, b->low[B], work);
#endif


	      work += (unsigned long) a->low[A] * (unsigned long) b->low[B];
	      carry += work >> LITTLENUM_NUMBER_OF_BITS;
	      work &= LITTLENUM_MASK;
#ifdef TRACE
	      printf ("work=%08x carry=%04x\n", work, carry);
#endif
	    }
	}
      significant |= work;
      if (significant || P < 0)
	{
	  if (P >= 0)
	    {
	      product->low[P] = work;
#ifdef TRACE
	      printf ("P=%d. work[p]:=%04x\n", P, work);
#endif
	    }
	  P++;
	}
      else
	{
	  extra_product_positions++;
	  exponent++;
	}
    }


#ifdef TRACE
  printf ("final carry =%04x\n", carry);
#endif
  if (carry)
    {
      if (extra_product_positions > 0)
	product->low[P] = carry;
      else
	{


	  exponent++;
	  P--;
	  for (q = product->low + P; q >= product->low; q--)
	    {
	      work = *q;
	      *q = carry;
	      carry = work;
	    }
	}
    }
  else
    P--;
  product->leader = product->low + P;
  product->exponent = exponent;
}
