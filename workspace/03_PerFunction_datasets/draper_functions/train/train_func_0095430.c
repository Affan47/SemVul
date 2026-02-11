rearrange_for_call(CSARG **args)
{
  CSARG *larg = NULL;
  CSARG *carg = *args;
  CSARG *vargs = NULL;
  int nargs = 0;


  while (carg)
  {
    nargs++;
    if (carg->op_type != CS_OP_COMMA)
    {

      if (vargs)
	carg->next = vargs;
      vargs = carg;
      break;
    }
    if (vargs)
      carg->expr1->next = vargs;
    vargs = carg->expr1;
    larg = carg;
    carg = carg->next;

    larg->next = NULL;
    larg->expr1 = NULL;
    dealloc_arg(&larg);
  }
  *args = vargs;

  return nargs;
}
