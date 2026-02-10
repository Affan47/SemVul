jbg_enc_free(struct jbg_enc_state *s)
{
  unsigned long stripe;
  int layer, plane;

#ifdef DEBUG
  fprintf(stderr, "jbg_enc_free(%p)\n", (void *) s);
#endif


  if (s->sde) {
    for (stripe = 0; stripe < s->stripes; stripe++) {
      for (layer = 0; layer < s->d + 1; layer++) {
	for (plane = 0; plane < s->planes; plane++)
	  if (s->sde[stripe][layer][plane] != SDE_DONE &&
	      s->sde[stripe][layer][plane] != SDE_TODO)
	    jbg_buf_free(&s->sde[stripe][layer][plane]);
	checked_free(s->sde[stripe][layer]);
      }
      checked_free(s->sde[stripe]);
    }
    checked_free(s->sde);
  }


  jbg_buf_free(&s->free_list);


  checked_free(s->s);


  checked_free(s->tp);


  checked_free(s->tx);


  if (s->lhp[1]) {
    for (plane = 0; plane < s->planes; plane++)
      checked_free(s->lhp[1][plane]);
    checked_free(s->lhp[1]);
  }


  checked_free(s->highres);

  return;
}
