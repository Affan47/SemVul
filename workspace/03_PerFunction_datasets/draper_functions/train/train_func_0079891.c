fmpz_poly_byte_unpack_unsigned(fmpz_poly_t poly_m, const mp_limb_t* array,
                               const unsigned long bundle, const unsigned long coeff_bytes)
{
   const unsigned long limbs_per_coeff = (coeff_bytes>>FLINT_LG_BYTES_PER_LIMB);
   const unsigned long extra_bytes_per_coeff = coeff_bytes
                                    - (limbs_per_coeff<<FLINT_LG_BYTES_PER_LIMB);

   const unsigned long limbs = ((coeff_bytes-1)>>FLINT_LG_BYTES_PER_LIMB) + 1;

   mp_limb_t* temp = (mp_limb_t*) flint_stack_alloc(limbs+2);

   unsigned long limb_upto = 0;
   unsigned long byte_offset = 0;

   fmpz_t coeff_m = poly_m->coeffs;
   unsigned long size_m = poly_m->limbs+1;
   poly_m->length = bundle;

   for (unsigned long i = 0; i < bundle; i++)
   {
       F_mpn_clear(temp, limbs+2);
       __fmpz_poly_unpack_bytes(temp + 1, array, limb_upto,
                                             byte_offset, coeff_bytes);
       temp[0] = limbs;
       NORM(temp);

       fmpz_add(coeff_m, coeff_m, temp);

       limb_upto += limbs_per_coeff;

       if (byte_offset + extra_bytes_per_coeff >= FLINT_BYTES_PER_LIMB)
       {
          limb_upto++;
          byte_offset = byte_offset + extra_bytes_per_coeff - FLINT_BYTES_PER_LIMB;
       } else
       {
          byte_offset = byte_offset + extra_bytes_per_coeff;
       }
       coeff_m += size_m;
   }
   flint_stack_release();
   _fmpz_poly_normalise(poly_m);
}
