_fmpz_poly_scalar_div_si(fmpz_poly_t output, const fmpz_poly_t poly, const long scalar)
{
   long x = scalar;

   if (poly->length == 0)
   {
      output->length = 0;
      return;
   }
   unsigned long size_out = output->limbs+1;
   unsigned long size1 = poly->limbs+1;
   fmpz_t coeffs_out = output->coeffs;
   fmpz_t coeffs1 = poly->coeffs;
   int sign = (x < 0L);
   if (sign) x = -x;
   mp_limb_t rem;

   if (poly->length > FLINT_POL_DIV_1_LENGTH)
   {
      unsigned long norm;
      mp_limb_t xinv;
      unsigned long xnorm;

      count_lead_zeros(norm, (unsigned long) x);
      xnorm = ((unsigned long) x<<norm);
      xinv = F_mpn_precompute_inverse(xnorm);

      for (unsigned long i = 0; i < poly->length; i++)
      {
         if (sign) coeffs_out[i*size_out] = -coeffs1[i*size1];
         else coeffs_out[i*size_out] = coeffs1[i*size1];
         rem = F_mpn_divrem_ui_precomp(coeffs_out+i*size_out+1, coeffs1+i*size1+1, ABS(coeffs1[i*size1]), x, xinv);
         if (((long) coeffs_out[i*size_out] < 0L) && (rem))
         {
            NORM(coeffs_out+i*size_out);
            fmpz_sub_ui_inplace(coeffs_out+i*size_out, 1UL);
         } else
         {
            NORM(coeffs_out+i*size_out);
         }
      }
   } else
   {
      for (unsigned long i = 0; i < poly->length; i++)
      {
         if (sign) coeffs_out[i*size_out] = -coeffs1[i*size1];
         else coeffs_out[i*size_out] = coeffs1[i*size1];
         rem = mpn_divmod_1(coeffs_out+i*size_out+1, coeffs1+i*size1+1, ABS(coeffs1[i*size1]), x);
         if (((long) coeffs_out[i*size_out] < 0L) && (rem))
         {
            NORM(coeffs_out+i*size_out);
            fmpz_sub_ui_inplace(coeffs_out+i*size_out, 1UL);
         } else
         {
            NORM(coeffs_out+i*size_out);
         }
      }
   }

   output->length = poly->length;
   _fmpz_poly_normalise(output);
}
