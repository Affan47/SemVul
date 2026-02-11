get_vectype_for_scalar_type_and_size (tree scalar_type, unsigned size)
{
  enum machine_mode inner_mode = TYPE_MODE (scalar_type);
  enum machine_mode simd_mode;
  unsigned int nbytes = GET_MODE_SIZE (inner_mode);
  int nunits;
  tree vectype;

  if (nbytes == 0)
    return NULL_TREE;

  if (GET_MODE_CLASS (inner_mode) != MODE_INT
      && GET_MODE_CLASS (inner_mode) != MODE_FLOAT)
    return NULL_TREE;


  if (INTEGRAL_TYPE_P (scalar_type)
      && (GET_MODE_BITSIZE (inner_mode) != TYPE_PRECISION (scalar_type)
	  || TREE_CODE (scalar_type) != INTEGER_TYPE))
    scalar_type = build_nonstandard_integer_type (GET_MODE_BITSIZE (inner_mode),
						  TYPE_UNSIGNED (scalar_type));


  else if (!SCALAR_FLOAT_TYPE_P (scalar_type)
	   && !INTEGRAL_TYPE_P (scalar_type)
	   && !POINTER_TYPE_P (scalar_type))
    scalar_type = lang_hooks.types.type_for_mode (inner_mode, 1);


  else if (nbytes < TYPE_ALIGN_UNIT (scalar_type))
    scalar_type = lang_hooks.types.type_for_mode (inner_mode,
						  TYPE_UNSIGNED (scalar_type));


  if (scalar_type == NULL_TREE)
    return NULL_TREE;


  if (size == 0)
    simd_mode = targetm.vectorize.preferred_simd_mode (inner_mode);
  else
    simd_mode = mode_for_vector (inner_mode, size / nbytes);
  nunits = GET_MODE_SIZE (simd_mode) / nbytes;
  if (nunits <= 1)
    return NULL_TREE;

  vectype = build_vector_type (scalar_type, nunits);
  if (vect_print_dump_info (REPORT_DETAILS))
    {
      fprintf (vect_dump, "get vectype with %d units of type ", nunits);
      print_generic_expr (vect_dump, scalar_type, TDF_SLIM);
    }

  if (!vectype)
    return NULL_TREE;

  if (vect_print_dump_info (REPORT_DETAILS))
    {
      fprintf (vect_dump, "vectype: ");
      print_generic_expr (vect_dump, vectype, TDF_SLIM);
    }

  if (!VECTOR_MODE_P (TYPE_MODE (vectype))
      && !INTEGRAL_MODE_P (TYPE_MODE (vectype)))
    {
      if (vect_print_dump_info (REPORT_DETAILS))
        fprintf (vect_dump, "mode not supported by target.");
      return NULL_TREE;
    }

  return vectype;
}
