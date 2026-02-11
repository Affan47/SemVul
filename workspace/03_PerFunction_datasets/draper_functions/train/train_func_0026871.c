build_type_no_quals (t)
     tree t;
{
  switch (TREE_CODE (t))
    {
    case POINTER_TYPE:
      return build_pointer_type (build_type_no_quals (TREE_TYPE (t)));
    case REFERENCE_TYPE:
      return build_reference_type (build_type_no_quals (TREE_TYPE (t)));
    default:
      return TYPE_MAIN_VARIANT (t);
    }
}
