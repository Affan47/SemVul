build_constructor (tree type, vec<constructor_elt, va_gc> *vals)
{
  tree c = make_node (CONSTRUCTOR);
  unsigned int i;
  constructor_elt *elt;
  bool constant_p = true;
  bool side_effects_p = false;

  TREE_TYPE (c) = type;
  CONSTRUCTOR_ELTS (c) = vals;

  FOR_EACH_VEC_SAFE_ELT (vals, i, elt)
    {


      if (!TREE_CONSTANT (elt->value))
	constant_p = false;
      if (TREE_SIDE_EFFECTS (elt->value))
	side_effects_p = true;
    }

  TREE_SIDE_EFFECTS (c) = side_effects_p;
  TREE_CONSTANT (c) = constant_p;

  return c;
}
