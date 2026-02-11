__zmod_poly_div_classical_mod_last(zmod_poly_t Q, zmod_poly_t A, zmod_poly_t B)
{
   if (B->length == 0)
   {
      printf("Error: Divide by zero\n");
      abort();
   }

   if (A->length < B->length)
   {
      zmod_poly_zero(Q);

      return;
   }

   unsigned long p = B->p;
   double p_inv = B->p_inv;
   unsigned long lead_inv = z_invert(B->coeffs[B->length - 1], p);
   unsigned long * coeff_Q;

   zmod_poly_t qB;
   zmod_poly_init2(qB, p, B->length);
   zmod_poly_t R;
   zmod_poly_init(R, p);

   zmod_poly_t Bm1;
   _zmod_poly_attach_truncate(Bm1, B, B->length - 1);

   long coeff = A->length - 1;

   zmod_poly_set(R, A);

   if (A->length >= B->length)
   {
      zmod_poly_fit_length(Q, A->length - B->length + 1);
      Q->length = A->length - B->length + 1;
   } else zmod_poly_zero(Q);

   coeff_Q = Q->coeffs - B->length + 1;

   while (coeff >= (long) B->length - 1)
   {
      R->coeffs[coeff] = z_mod_precomp(R->coeffs[coeff], p, p_inv);

      while ((coeff >= (long) B->length - 1) && (R->coeffs[coeff] == 0L))
      {
         coeff_Q[coeff] = 0L;
         coeff--;
         if (coeff >= (long) B->length - 1) R->coeffs[coeff] = z_mod_precomp(R->coeffs[coeff], p, p_inv);
      }

      if (coeff >= (long) B->length - 1)
      {
         coeff_Q[coeff] = z_mulmod_precomp(R->coeffs[coeff], lead_inv, p, p_inv);

         if (coeff >= (long) B->length)
         {
            zmod_poly_scalar_mul(qB, Bm1, z_negmod(coeff_Q[coeff], p));

            zmod_poly_t R_sub;
            R_sub->p = p;
            R_sub->coeffs = R->coeffs + coeff - B->length + 1;
            R_sub->length = B->length - 1;
            _zmod_poly_add_without_mod(R_sub, R_sub, qB);
         }

         coeff--;
      }
   }

   zmod_poly_clear(R);
   zmod_poly_clear(qB);
}
