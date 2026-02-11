mpn_fft_norm_modF (mp_ptr rp, mp_size_t n, mp_srcptr ap, mp_size_t an, int b)
{
  if (an <= n)
    {
#ifdef COUNT_ZEROCOPY
      printf ("mpn_fft_norm_modF: MPN_FFT_COPY with %d limbs\n", an);
#endif
      MPN_COPY (rp, ap, an);
      if (an < n)
	MPN_FFT_ZERO (rp + an, n - an);
      return 0;
    }
  else
    {
      mp_size_t l;
      mp_limb_t cc;
      int i;

      l = (an <= 2 * n) ? an - n : n;
      if (b == -1)
	cc = mpn_add (rp, ap, n, ap + n, l);
      else
	cc = -mpn_sub (rp, ap, n, ap + n, l);
      ap += n + l;
      an -= n + l;
      for (i = -1; an > 0; i = -b * i)
	{
	  l = (an <= n) ? an : n;
	  if (i == -1)
	    cc += mpn_add (rp, rp, n, ap, l);
	  else
	    cc -= mpn_sub (rp, rp, n, ap, l);
	  ap += l;
	  an -= l;
	}
      if (b == 1)
	{
	  if (cc & GMP_LIMB_HIGHBIT)
	    cc = mpn_add_1 (rp, rp, n, -cc);
	  cc = mpn_sub_1 (rp, rp, n, cc);
	}
      else
	cc = mpn_add_1 (rp, rp, n, cc);
      return mpn_add_1 (rp, rp, n, cc);
    }
}
