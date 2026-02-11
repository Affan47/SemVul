fmpz_poly_evaluate_mod(fmpz_poly_t poly, ulong p,
		                               ulong e, pre_inv_t pinv)
{
    if (poly->length == 0)
	    return 0;

    if (e == 0)
        return fmpz_mod_ui(poly->coeffs, p);

    unsigned long sizef = poly->limbs+1;
    fmpz_t ccoeff = poly->coeffs + (poly->length - 1)*sizef;
    unsigned long cmod_coeff;
    unsigned long res = 0;

#if FLINT_BITS == 64
	if (FLINT_BIT_COUNT(p) > FLINT_D_BITS)
	{
	   for (long i = 0;  i < poly->length; i++)
       {
          cmod_coeff = fmpz_mod_ui(ccoeff, p);
          res = z_addmod(z_mulmod2_precomp(res, e, p, pinv), cmod_coeff, p);
          ccoeff -= sizef;
       }
	} else
	{
#endif
	   for (long i = 0; i < poly->length; i++)
       {
          cmod_coeff = fmpz_mod_ui(ccoeff, p);
          res = z_addmod(z_mulmod_precomp(res, e, p, pinv), cmod_coeff, p);
          ccoeff -= sizef;
       }
#if FLINT_BITS == 64
   }
#endif

    return res;
}
