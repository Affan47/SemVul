build_distinct_type_copy (tree type)
{
  tree t = copy_node (type);

  TYPE_POINTER_TO (t) = 0;
  TYPE_REFERENCE_TO (t) = 0;


  if (TYPE_STRUCTURAL_EQUALITY_P (type))
    SET_TYPE_STRUCTURAL_EQUALITY (t);
  else
    TYPE_CANONICAL (t) = t;


  TYPE_MAIN_VARIANT (t) = t;
  TYPE_NEXT_VARIANT (t) = 0;


  return t;
}
