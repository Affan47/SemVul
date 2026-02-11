mpc_define(mpc_parser_t *p, mpc_parser_t *a) {

  if (p->retained) {
    p->type = a->type;
    p->data = a->data;
  } else {
    mpc_parser_t *a2 = mpc_failf("Attempt to assign to Unretained Parser!");
    p->type = a2->type;
    p->data = a2->data;
    free(a2);
  }

  free(a);
  return p;
}
