zap_term_special(struct term *t)
{
  struct rel *r1, *r2;

  if (t->occ.rel != NULL) {
    printf("WARNING, zap_term_special called with contained term: ");
    print_term(stdout, t);
    printf("\n");
  }
  else if (t->fpa_id != 0)
    t->fpa_id--;
  else {
    if (t->type == COMPLEX) {
      r1 = t->farg;
      while (r1 != NULL) {
	zap_term_special(r1->argval);
	r2 = r1;
	r1 = r1->narg;
	free_rel(r2);
      }
    }
    free_term(t);
  }
}
