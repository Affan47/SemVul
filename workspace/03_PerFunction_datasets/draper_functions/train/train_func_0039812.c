mpc_div_inf_fin (mpc_ptr rop, mpc_srcptr z, mpc_srcptr w)


{
   int a, b, x, y;

   a = (mpfr_inf_p (mpc_realref (z)) ? MPFR_SIGNBIT (mpc_realref (z)) : 0);
   b = (mpfr_inf_p (mpc_imagref (z)) ? MPFR_SIGNBIT (mpc_imagref (z)) : 0);


   if (a == 0 || b == 0) {

      x = a * MPC_MPFR_SIGN (mpc_realref (w)) + b * MPC_MPFR_SIGN (mpc_imagref (w));
      y = b * MPC_MPFR_SIGN (mpc_realref (w)) - a * MPC_MPFR_SIGN (mpc_imagref (w));
   }
   else {


      mpfr_t sign;

      mpfr_init2 (sign, 2);


      if (a == 1)
         if (b == 1) {
            mpfr_add (sign, mpc_realref (w), mpc_imagref (w), GMP_RNDN);
            x = MPC_MPFR_SIGN (sign);
            mpfr_sub (sign, mpc_realref (w), mpc_imagref (w), GMP_RNDN);
            y = MPC_MPFR_SIGN (sign);
         }
         else {
            mpfr_sub (sign, mpc_realref (w), mpc_imagref (w), GMP_RNDN);
            x = MPC_MPFR_SIGN (sign);
            mpfr_add (sign, mpc_realref (w), mpc_imagref (w), GMP_RNDN);
            y = -MPC_MPFR_SIGN (sign);
         }
      else
         if (b == 1) {
            mpfr_sub (sign, mpc_imagref (w), mpc_realref (w), GMP_RNDN);
            x = MPC_MPFR_SIGN (sign);
            mpfr_add (sign, mpc_realref (w), mpc_imagref (w), GMP_RNDN);
            y = MPC_MPFR_SIGN (sign);
         }
         else {
            mpfr_add (sign, mpc_realref (w), mpc_imagref (w), GMP_RNDN);
            x = -MPC_MPFR_SIGN (sign);
            mpfr_sub (sign, mpc_imagref (w), mpc_realref (w), GMP_RNDN);
            y = MPC_MPFR_SIGN (sign);
         }
      mpfr_clear (sign);
   }

   if (x == 0)
      mpfr_set_nan (mpc_realref (rop));
   else
      mpfr_set_inf (mpc_realref (rop), x);
   if (y == 0)
      mpfr_set_nan (mpc_imagref (rop));
   else
      mpfr_set_inf (mpc_imagref (rop), y);

   return MPC_INEX (0, 0);
}
