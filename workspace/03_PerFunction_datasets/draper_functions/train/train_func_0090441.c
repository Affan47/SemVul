real_isa(OBJECT x, OBJECT y) {
  while (1) {
    if (x == NULL)
      return 0;

    if (x == y)
      return 1;

    if (x->parents == NULL)
      return 0;

    if (OBJECTP(x->parents)) {
      x = (OBJECT) x->parents;
      continue;
    }

    if (VECTORP(x->parents)) {
      int i;
      VECTOR vxp = (VECTOR) x->parents;

      for (i = 0; i < vxp->_.length; i++)
	if (real_isa((OBJECT) AT(vxp, i), y))
	  return 1;

      return 0;
    }

    return 0;
  }
}
