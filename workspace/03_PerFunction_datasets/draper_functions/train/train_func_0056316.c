unify(Term t1, Context c1,
	   Term t2, Context c2, Trail *trp)
{
  Trail tpos, tp, t3;
  int vn1, vn2;

  DEREFERENCE(t1, c1)

  DEREFERENCE(t2, c2)


  if (VARIABLE(t1)) {
    vn1 = VARNUM(t1);
    if (VARIABLE(t2)) {

      if (vn1 == VARNUM(t2) && c1 == c2)
	return TRUE;
      else {
	BIND_TR(vn1, c1, t2, c2, trp)
	return TRUE;
      }
    }
    else {

      if (occur_check(vn1, c1, t2, c2)) {
	BIND_TR(vn1, c1, t2, c2, trp)
	return TRUE;
      }
      else
	return FALSE;
    }
  }

  else if (VARIABLE(t2)) {

    vn2 = VARNUM(t2);
    if (occur_check(vn2, c2, t1, c1)) {
      BIND_TR(vn2, c2, t1, c1, trp)
      return TRUE;
    }
    else
      return FALSE;
  }

  else if (SYMNUM(t1) != SYMNUM(t2))
    return FALSE;

  else if (ARITY(t1) == 0)
    return TRUE;

  else {
    int i, arity;

    tpos = *trp;

    i = 0; arity = ARITY(t1);
    while (i < arity && unify(ARG(t1,i), c1, ARG(t2,i), c2, trp))
      i++;

    if (i == arity)
      return TRUE;
    else {
      tp = *trp;
      while (tp != tpos) {
	tp->context->terms[tp->varnum] = NULL;
	tp->context->contexts[tp->varnum] = NULL;
	t3 = tp;
	tp = tp->next;
	free_trail(t3);
      }
      *trp = tpos;
      return FALSE;
    }
  }
}
