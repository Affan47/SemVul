fix_sign (mpc_ptr z, int sign_eps, int sign_a, mpfr_srcptr y)
{
  int ymod4 = -1;
  mpfr_exp_t ey;
  mpz_t my;
  unsigned long int t;

  mpz_init (my);

  ey = mpfr_get_z_exp (my, y);

  t = mpz_scan1 (my, 0);
  ey += (mpfr_exp_t) t;
  mpz_tdiv_q_2exp (my, my, t);


  if (ey >= 2)
    ymod4 = 0;
  else if (ey == 1)
    ymod4 = mpz_tstbit (my, 0) * 2;
  else if (ey == 0)
    {
      ymod4 = mpz_tstbit (my, 1) * 2 + mpz_tstbit (my, 0);
      if (mpz_cmp_ui (my , 0) < 0)
        ymod4 = 4 - ymod4;
    }
  else
    goto end;

  if (mpfr_zero_p (mpc_realref(z)))
    {


      MPC_ASSERT (ymod4 == 1 || ymod4 == 3);
      if ((ymod4 == 3 && sign_eps == 0) ||
          (ymod4 == 1 && sign_eps == 1))
        mpfr_neg (mpc_realref(z), mpc_realref(z), GMP_RNDZ);
    }
  else if (mpfr_zero_p (mpc_imagref(z)))
    {


      MPC_ASSERT (ymod4 == 0 || ymod4 == 2);
      if ((ymod4 == 0 && sign_a == sign_eps) ||
          (ymod4 == 2 && sign_a != sign_eps))
        mpfr_neg (mpc_imagref(z), mpc_imagref(z), GMP_RNDZ);
    }

 end:
  mpz_clear (my);
}
