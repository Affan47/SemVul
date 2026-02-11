mpn_fft_normalize (mp_ptr ap, mp_size_t n)
{
  if (ap[n] != 0)
    {
      MPN_DECR_U (ap, n + 1, ONE);
      if (ap[n] == 0)
	{


	  MPN_FFT_ZERO (ap, n);
	  ap[n] = 1;
	}
      else
	ap[n] = 0;
    }
}
