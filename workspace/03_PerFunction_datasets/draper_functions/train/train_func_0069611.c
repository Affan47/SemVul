mpc_test_pass(mpc_parser_t *p, const char *s, const void *d,
  int(*tester)(const void*, const void*),
  mpc_dtor_t destructor,
  void(*printer)(const void*)) {

  mpc_result_t r;
  if (mpc_parse("<test>", s, p, &r)) {

    if (tester(r.output, d)) {
      destructor(r.output);
      return 1;
    } else {
      printf("Got "); printer(r.output); printf("\n");
      printf("Expected "); printer(d); printf("\n");
      destructor(r.output);
      return 0;
    }

  } else {
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
    return 0;

  }

}
