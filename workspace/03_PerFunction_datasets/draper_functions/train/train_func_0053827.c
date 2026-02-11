check_NAN (void)
{
  mpfr_t t, ch,sh,th,ach,ash,ath;
  int tester;
  int fail = 0;

  mpfr_init2(t,200);
  mpfr_init2(ch,200);
  mpfr_init2(sh,200);
  mpfr_init2(th,200);
  mpfr_init2(ach,200);
  mpfr_init2(ash,200);
  mpfr_init2(ath,200);

  MPFR_SET_NAN(t);


  tester=mpfr_cosh(ch,t,MPFR_RNDD);
  if (!MPFR_IS_NAN(ch) || tester!=0)
    {
      printf("cosh NAN \n");
      fail = 1;
      goto clean_up;
    }


  tester=mpfr_sinh(sh,t,MPFR_RNDD);
  if (!MPFR_IS_NAN(sh) || tester!=0)
    {
      printf("sinh NAN \n");
      fail = 1;
      goto clean_up;
    }


  tester=mpfr_tanh(th,t,MPFR_RNDD);
  if (!MPFR_IS_NAN(th) || tester!=0)
    {
      printf("tanh NAN \n");
      fail = 1;
      goto clean_up;
    }


  tester=mpfr_acosh(ach,t,MPFR_RNDD);
  if (!MPFR_IS_NAN(ach) || tester!=0)
    {
      printf("acosh NAN \n");
      fail = 1;
      goto clean_up;
    }


  tester=mpfr_asinh(ash,t,MPFR_RNDD);
  if (!MPFR_IS_NAN(ash) || tester!=0)
    {
      printf("asinh NAN \n");
      fail = 1;
      goto clean_up;
    }


  tester=mpfr_atanh(ath,t,MPFR_RNDD);
  if (!MPFR_IS_NAN(ath) || tester!=0)
    {
      printf("atanh NAN \n");
      fail = 1;
      goto clean_up;
    }

 clean_up:
  mpfr_clear(t);
  mpfr_clear(ch);
  mpfr_clear(sh);
  mpfr_clear(th);
  mpfr_clear(ach);
  mpfr_clear(ash);
  mpfr_clear(ath);

  return fail;
}
