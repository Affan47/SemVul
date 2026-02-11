btor (int binary, const rpf_t *rpf)


{
   unsigned int	mantissa;
   int		sign, exponent;
   union
   {
      float f;
      unsigned char c[4];
   } value;

   if (binary == RPF_ZERO)
      return 0;

   if (binary < 0 || binary >= 1 << (rpf->mantissa_bits + 1))
      error ("Reduced precision format: value %d out of range.", binary);


   sign       = binary & 1;
   mantissa   = (binary & ((1 << (rpf->mantissa_bits + 1)) - 1)) >> 1;
   mantissa <<= (23 - rpf->mantissa_bits);
   exponent   = 0;

   if (mantissa == 0)
   {
      value.f = (sign ? -1.0 : 1.0);
   }
   else
   {
      while (!(mantissa & (1 << 22)))
      {
	 exponent--;
	 mantissa <<= 1;
      }
      mantissa <<= 1;

      value.c[BYTE_0] = (sign << 7) | ((exponent + 126) >> 1);
      value.c[BYTE_1] = (((exponent + 126) & 1) << 7)
			| ((mantissa  >> 16) & 127);
      value.c[BYTE_2] = (mantissa >> 8) & 255;
      value.c[BYTE_3] = mantissa & 255;
   }

   return value.f * rpf->range;

}
