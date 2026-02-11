utest_logf(ESL_GETOPTS *go)
{
  __m128 x;
  union { __m128 v; float x[4]; } r;


  x   = _mm_set_ps(0.0, -0.0, -1.0, -eslINFINITY);
  r.v =  esl_sse_logf(x);
  if (esl_opt_GetBoolean(go, "-v")) {
    printf("logf");
    esl_sse_dump_ps(stdout, x);    printf(" ==> ");
    esl_sse_dump_ps(stdout, r.v);  printf("\n");
  }
  if (! isnan(r.x[0]))                 esl_fatal("logf(-inf) should be NaN");
  if (! isnan(r.x[1]))                 esl_fatal("logf(-1)   should be NaN");
  if (! isnan(r.x[2]))                 esl_fatal("logf(-0)   should be NaN");
  if (! (r.x[3] < 0 && isinf(r.x[3]))) esl_fatal("logf(0)    should be -inf");

  x   = _mm_set_ps(FLT_MAX, FLT_MIN, eslNaN, eslINFINITY);
  r.v = esl_sse_logf(x);
  if (esl_opt_GetBoolean(go, "-v")) {
    printf("logf");
    esl_sse_dump_ps(stdout, x);    printf(" ==> ");
    esl_sse_dump_ps(stdout, r.v);  printf("\n");
  }
  if (! isinf(r.x[0]))  esl_fatal("logf(inf)  should be inf");
  if (! isnan(r.x[1]))  esl_fatal("logf(NaN)  should be NaN");

}
