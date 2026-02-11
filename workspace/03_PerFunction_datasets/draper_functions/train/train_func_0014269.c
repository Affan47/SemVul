checktreerep(Outchoices *od, Hashtable *tp, choice rep,
		     choice requests, cutfnp cutfn) {
  unsigned long i;

  for (i = 0; i < tp->size; i++) {
    if (checkonerep(od, tp->head[i], rep, requests, cutfn, NULL, NULL))
      return(TRUE);
  }
  return(FALSE);
}
