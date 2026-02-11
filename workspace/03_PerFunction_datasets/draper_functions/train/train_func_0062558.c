cp_reconstruct_complex_type (tree type, tree bottom)
{
  tree inner, outer;

  if (TREE_CODE (type) == POINTER_TYPE)
    {
      inner = cp_reconstruct_complex_type (TREE_TYPE (type), bottom);
      outer = build_pointer_type_for_mode (inner, TYPE_MODE (type),
					   TYPE_REF_CAN_ALIAS_ALL (type));
    }
  else if (TREE_CODE (type) == REFERENCE_TYPE)
    {
      inner = cp_reconstruct_complex_type (TREE_TYPE (type), bottom);
      outer = build_reference_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  else if (TREE_CODE (type) == ARRAY_TYPE)
    {
      inner = cp_reconstruct_complex_type (TREE_TYPE (type), bottom);
      outer = build_cplus_array_type (inner, TYPE_DOMAIN (type));


      return outer;
    }
  else if (TREE_CODE (type) == FUNCTION_TYPE)
    {
      inner = cp_reconstruct_complex_type (TREE_TYPE (type), bottom);
      outer = build_function_type (inner, TYPE_ARG_TYPES (type));
      outer = apply_memfn_quals (outer,
				 type_memfn_quals (type),
				 type_memfn_rqual (type));
    }
  else if (TREE_CODE (type) == METHOD_TYPE)
    {
      inner = cp_reconstruct_complex_type (TREE_TYPE (type), bottom);


      outer
	= build_method_type_directly
	    (class_of_this_parm (type), inner,
	     TREE_CHAIN (TYPE_ARG_TYPES (type)));
    }
  else if (TREE_CODE (type) == OFFSET_TYPE)
    {
      inner = cp_reconstruct_complex_type (TREE_TYPE (type), bottom);
      outer = build_offset_type (TYPE_OFFSET_BASETYPE (type), inner);
    }
  else
    return bottom;

  if (TYPE_ATTRIBUTES (type))
    outer = cp_build_type_attribute_variant (outer, TYPE_ATTRIBUTES (type));
  return cp_build_qualified_type (outer, cp_type_quals (type));
}
