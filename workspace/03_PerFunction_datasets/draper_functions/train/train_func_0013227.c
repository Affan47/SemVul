fmpz_poly_limb_pack_neg_1(mp_limb_t * array, const fmpz_poly_t poly_fmpz)
{
   unsigned long size_m = poly_fmpz->limbs + 1;
   long size_j;
   fmpz_t coeffs_m = poly_fmpz->coeffs;
	unsigned long length = poly_fmpz->length;
   long carry = 0;

   for (unsigned long i = 0, j = 0, k = 0; i < length; i++, j += size_m, k++)
   {
      size_j = (long) coeffs_m[j];
      if (size_j > 0L)
      {
         if (carry) array[k] = -coeffs_m[j + 1] - 1;
         else array[k] = -coeffs_m[j + 1];
			carry = 1L;
      } else if (size_j < 0L)
      {
         if (carry) array[k] = coeffs_m[j + 1] - 1;
         else array[k] = coeffs_m[j + 1];
			carry = 0L;
      } else
      {
         if (carry)
         {
            array[k] = -1L;
				carry = 1L;
         } else
         {
            array[k] = 0L;
				carry = 0L;
         }
      }
   }
}
