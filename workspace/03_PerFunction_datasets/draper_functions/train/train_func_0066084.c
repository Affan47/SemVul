_zmod_poly_mul_KS(zmod_poly_t output, zmod_poly_p input1, zmod_poly_p input2, unsigned long bits_input)
{
   unsigned long length1 = input1->length;
   unsigned long length2 = input2->length;

   if ((length1 == 0) || (length2 == 0))
   {
      zmod_poly_zero(output);
      return;
   }

   unsigned long final_length = length1 + length2 - 1;

   if (length2 > length1)
   {
      unsigned long temp = length1;
      length1 = length2;
      length2 = temp;
      SWAP_ZMOD_POLY_PTRS(input1, input2);
   }

   unsigned long bits1, bits2;

   bits1 = zmod_poly_bits(input1);
   bits2 = (input1 == input2) ? bits1 : zmod_poly_bits(input2);

   unsigned long length = length2;
   unsigned log_length = 0;
   while ((1<<log_length) < length) log_length++;
   unsigned long bits = bits1 + bits2 + log_length;

   if (bits_input)
   {
      bits = bits_input;
   }

   mp_limb_t *mpn1, *mpn2, *res;

   unsigned long limbs1, limbs2;

   limbs1 = FLINT_MAX((long)((length1 * bits-1) / FLINT_BITS + 1), 0L);
   limbs2 = FLINT_MAX((long)((length2 * bits-1) / FLINT_BITS + 1), 0L);

   mpn1 = (mp_limb_t*) flint_stack_alloc(limbs1);
   mpn2 = (input1 == input2) ? mpn1 : (mp_limb_t*) flint_stack_alloc(limbs2);

   _zmod_poly_bit_pack_mpn(mpn1, input1, bits, length1);

   if(input1 != input2)
      _zmod_poly_bit_pack_mpn(mpn2, input2, bits, length2);

   res = (mp_limb_t*) flint_stack_alloc(limbs1+limbs2);
   res[limbs1+limbs2-1] = 0L;

   if (input1 != input2) F_mpn_mul(res, mpn1, limbs1, mpn2, limbs2);
   else F_mpn_mul(res, mpn1, limbs1, mpn1, limbs1);

   _zmod_poly_bit_unpack_mpn(output, res, length1 + length2 - 1, bits);

   flint_stack_release();
   flint_stack_release();
   if(input1 != input2)
      flint_stack_release();

   output->length = final_length;


   __zmod_poly_normalise(output);
}
