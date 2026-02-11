build_state(s, d)
     int s;
     struct dfa *d;
{
  int *trans;
  int i;


  if (d->trcount >= 1024)
    {
      for (i = 0; i < d->tralloc; ++i)
	if (d->trans[i])
	  {
	    free((ptr_t) d->trans[i]);
	    d->trans[i] = NULL;
	  }
	else if (d->fails[i])
	  {
	    free((ptr_t) d->fails[i]);
	    d->fails[i] = NULL;
	  }
      d->trcount = 0;
    }

  ++d->trcount;


  d->success[s] = 0;
  if (ACCEPTS_IN_CONTEXT(d->states[s].newline, 1, d->states[s].letter, 0,
      s, *d))
    d->success[s] |= 4;
  if (ACCEPTS_IN_CONTEXT(d->states[s].newline, 0, d->states[s].letter, 1,
      s, *d))
    d->success[s] |= 2;
  if (ACCEPTS_IN_CONTEXT(d->states[s].newline, 0, d->states[s].letter, 0,
      s, *d))
    d->success[s] |= 1;

  MALLOC(trans, int, NOTCHAR);
  dfastate(s, d, trans);


  for (i = 0; i < NOTCHAR; ++i)
    if (trans[i] >= d->tralloc)
      {
	int oldalloc = d->tralloc;

	while (trans[i] >= d->tralloc)
	  d->tralloc *= 2;
	REALLOC(d->realtrans, int *, d->tralloc + 1);
	d->trans = d->realtrans + 1;
	REALLOC(d->fails, int *, d->tralloc);
	REALLOC(d->success, int, d->tralloc);
	REALLOC(d->newlines, int, d->tralloc);
	while (oldalloc < d->tralloc)
	  {
	    d->trans[oldalloc] = NULL;
	    d->fails[oldalloc++] = NULL;
	  }
      }


  d->newlines[s] = trans['\n'];
  trans['\n'] = -1;

  if (ACCEPTING(s, *d))
    d->fails[s] = trans;
  else
    d->trans[s] = trans;
}
