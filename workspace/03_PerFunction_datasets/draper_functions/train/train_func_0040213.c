mpc_ui_ui_sub (mpc_ptr rop, unsigned long int re, unsigned long int im,
               mpc_srcptr op, mpc_rnd_t rnd)
{
   int inex_re, inex_im;

   inex_re = mpfr_ui_sub (mpc_realref (rop), re, mpc_realref (op), MPC_RND_RE (rnd));
   inex_im = mpfr_ui_sub (mpc_imagref (rop), im, mpc_imagref (op), MPC_RND_IM (rnd));

   return MPC_INEX (inex_re, inex_im);
}
