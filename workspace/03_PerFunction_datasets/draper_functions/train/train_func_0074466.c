flatten_top(Formula f)
{
  if (f->type != AND_FORM && f->type != OR_FORM)
    return f;
  else {
    BOOL operate = FALSE;
    int n = 0;
    int i;
    for (i = 0; i < f->arity; i++) {
      if (f->type != f->kids[i]->type)
	n++;
      else {
	n += (f->kids[i]->arity);
	operate = TRUE;
      }
    }
    if (!operate)
      return f;
    else {
      Formula g = formula_get(n, f->type);
      int i, j;
      j = 0;
      for (i = 0; i < f->arity; i++) {
	if (f->kids[i]->type != f->type)
	  g->kids[j++] = f->kids[i];
	else {
	  int k;
	  for (k = 0; k < f->kids[i]->arity; k++)
	    g->kids[j++] = f->kids[i]->kids[k];
	  free_formula(f->kids[i]);
	}
      }
      free_formula(f);

      if (g->arity == 1) {
	Formula h = g->kids[0];
	free_formula(g);
	return h;
      }
      else
	return g;
    }
  }
}
