zmod_poly_make_monic(zmod_poly_t output, zmod_poly_t pol)
{
   if (!pol->length)
   {
      output->length = 0;
      return;
   }

   unsigned long lead_inv = pol->coeffs[pol->length-1];

   if (lead_inv == 1L)
   {
      zmod_poly_set(output, pol);
      return;
   }

   lead_inv = z_invert(lead_inv, pol->p);

   zmod_poly_scalar_mul(output, pol, lead_inv);
}
