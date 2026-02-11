jvp_dtoa_context_free(struct dtoa_context* C) {
  int k;
  while (C->p5s) {
    Bigint* p5 = C->p5s;
    C->p5s = p5->next;
    Bfree(C, p5);
  }
  for (k=0; k<(int)(sizeof(C->freelist)/sizeof(C->freelist[0])); k++) {
    while (C->freelist[k]) {
      Bigint* v = C->freelist[k];
      C->freelist[k] = v->next;
      FREE(v);
    }
  }
}
