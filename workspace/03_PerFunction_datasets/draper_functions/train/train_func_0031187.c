build_constructor (tree type, VEC(constructor_elt,gc) *vals)
{
  tree c = make_node (CONSTRUCTOR);
  unsigned int i;
  constructor_elt *elt;
  bool constant_p = true;

  TREE_TYPE (c) = type;
  CONSTRUCTOR_ELTS (c) = vals;

  FOR_EACH_VEC_ELT (constructor_elt, vals, i, elt)
    if (!TREE_CONSTANT (elt->value))
      {
	constant_p = false;
	break;
      }

  TREE_CONSTANT (c) = constant_p;

  return c;
}
