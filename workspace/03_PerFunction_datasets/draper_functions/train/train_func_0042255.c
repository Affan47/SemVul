build_method_type_directly (tree basetype,
			    tree rettype,
			    tree argtypes)
{
  tree t;
  tree ptype;
  int hashcode = 0;
  bool any_structural_p, any_noncanonical_p;
  tree canon_argtypes;


  t = make_node (METHOD_TYPE);

  TYPE_METHOD_BASETYPE (t) = TYPE_MAIN_VARIANT (basetype);
  TREE_TYPE (t) = rettype;
  ptype = build_pointer_type (basetype);


  argtypes = tree_cons (NULL_TREE, ptype, argtypes);
  TYPE_ARG_TYPES (t) = argtypes;


  hashcode = iterative_hash_object (TYPE_HASH (basetype), hashcode);
  hashcode = iterative_hash_object (TYPE_HASH (rettype), hashcode);
  hashcode = type_hash_list (argtypes, hashcode);
  t = type_hash_canon (hashcode, t);


  any_structural_p
    = (TYPE_STRUCTURAL_EQUALITY_P (basetype)
       || TYPE_STRUCTURAL_EQUALITY_P (rettype));
  any_noncanonical_p
    = (TYPE_CANONICAL (basetype) != basetype
       || TYPE_CANONICAL (rettype) != rettype);
  canon_argtypes = maybe_canonicalize_argtypes (TREE_CHAIN (argtypes),
						&any_structural_p,
						&any_noncanonical_p);
  if (any_structural_p)
    SET_TYPE_STRUCTURAL_EQUALITY (t);
  else if (any_noncanonical_p)
    TYPE_CANONICAL (t)
      = build_method_type_directly (TYPE_CANONICAL (basetype),
				    TYPE_CANONICAL (rettype),
				    canon_argtypes);
  if (!COMPLETE_TYPE_P (t))
    layout_type (t);

  return t;
}
