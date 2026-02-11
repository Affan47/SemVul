check_various (void)
{
  mpf_t got, u, v;

  mpf_init (got);
  mpf_init (u);
  mpf_init (v);


  mpf_set_prec (got, 20L);
  mpf_set_ui (u, 100L);
  mpf_set_ui (v, 4L);
  mpf_div (got, u, v);
  MPF_CHECK_FORMAT (got);
  ASSERT_ALWAYS (mpf_cmp_ui (got, 25L) == 0);


  mpf_set_prec (got, 500L);
  mpf_set_prec (v, 900L);
  mpf_set_ui (v, 1L);
  mpf_mul_2exp (v, v, 800L);
  mpf_add_ui (v, v, 1L);
  mpf_div (got, u, v);
  check_one ("1/2^n+1, separate", got, u, v);

  mpf_clear (got);
  mpf_clear (u);
  mpf_clear (v);
}
