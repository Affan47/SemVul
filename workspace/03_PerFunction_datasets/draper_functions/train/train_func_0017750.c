build_list_conv (tree type, tree ctor, int flags)
{
  tree elttype = TREE_VEC_ELT (CLASSTYPE_TI_ARGS (type), 0);
  unsigned len = CONSTRUCTOR_NELTS (ctor);
  conversion **subconvs = alloc_conversions (len);
  conversion *t;
  unsigned i;
  tree val;


  flags &= ~LOOKUP_NO_CONVERSION;

  flags |= LOOKUP_NO_NARROWING;

  FOR_EACH_CONSTRUCTOR_VALUE (CONSTRUCTOR_ELTS (ctor), i, val)
    {
      conversion *sub
	= implicit_conversion (elttype, TREE_TYPE (val), val,
			       false, flags);
      if (sub == NULL)
	return NULL;

      subconvs[i] = sub;
    }

  t = alloc_conversion (ck_list);
  t->type = type;
  t->u.list = subconvs;
  t->rank = cr_exact;

  for (i = 0; i < len; ++i)
    {
      conversion *sub = subconvs[i];
      if (sub->rank > t->rank)
	t->rank = sub->rank;
      if (sub->user_conv_p)
	t->user_conv_p = true;
      if (sub->bad_p)
	t->bad_p = true;
    }

  return t;
}
