maketree(Tree *treex, Hashindex *gooditems, Hashindex *baditems,
	      choice datacols[OUTCOME_NUMBER][DATACOLS_NUMBER][2],
	      unsigned int data_number) {
  Hashindex *p;
  char *name, *nameend;

  for (p = gooditems; p != NULL; TO_NEXT(p)) {
    if (p->own != NULL) {
      name = NULL;
      treex->cutfn(&name, &nameend, p->name, FALSE);
      (void)treefind(name, nameend, &(treex->tree), p, treex->cutfn, FALSE,
		     FALSE, TRUE, treex->space, datacols, data_number);
    }
  }
  for (p = baditems; p != NULL; TO_NEXT(p)) {
    if (p->own != NULL) {
      name = NULL;
      treex->cutfn(&name, &nameend, p->name, FALSE);
      (void)treefind(name, nameend, &(treex->tree), p, treex->cutfn, FALSE,
		     FALSE, TRUE, treex->space, datacols, data_number);
    }
  }
}
