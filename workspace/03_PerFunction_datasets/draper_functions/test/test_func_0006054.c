exp_unop (int code, etree_type *child)
{
  etree_type value, *new_e;

  value.unary.type.node_code = code;
  value.unary.type.filename = child->type.filename;
  value.unary.type.lineno = child->type.lineno;
  value.unary.child = child;
  value.unary.type.node_class = etree_unary;
  exp_fold_tree_no_dot (&value);
  if (expld.result.valid_p)
    return exp_intop (expld.result.value);

  new_e = (etree_type *) stat_alloc (sizeof (new_e->unary));
  memcpy (new_e, &value, sizeof (new_e->unary));
  return new_e;
}
