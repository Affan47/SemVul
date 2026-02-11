build_array_type (tree elt_type, tree index_type)
{
  tree t;
  unsigned int hashcode;

  if (TREE_CODE (elt_type) == FUNCTION_TYPE)
    {
      error ("arrays of functions are not meaningful");
      elt_type = integer_type_node;
    }


  build_pointer_type (elt_type);


  t = make_node (ARRAY_TYPE);
  TREE_TYPE (t) = elt_type;
  TYPE_DOMAIN (t) = index_type;

  if (index_type == 0)
    {
      return t;
    }

  hashcode = TYPE_HASH (elt_type) + TYPE_HASH (index_type);
  t = type_hash_canon (hashcode, t);

  if (!COMPLETE_TYPE_P (t))
    layout_type (t);
  return t;
}
