parser_build_binary_op (location_t location, enum tree_code code,
			struct c_expr arg1, struct c_expr arg2)
{
  struct c_expr result;

  enum tree_code code1 = arg1.original_code;
  enum tree_code code2 = arg2.original_code;
  tree type1 = (arg1.original_type
                ? arg1.original_type
                : TREE_TYPE (arg1.value));
  tree type2 = (arg2.original_type
                ? arg2.original_type
                : TREE_TYPE (arg2.value));

  result.value = build_binary_op (location, code,
				  arg1.value, arg2.value, 1);
  result.original_code = code;
  result.original_type = NULL;

  if (TREE_CODE (result.value) == ERROR_MARK)
    return result;

  if (location != UNKNOWN_LOCATION)
    protected_set_expr_location (result.value, location);


  if (warn_parentheses)
    warn_about_parentheses (code, code1, arg1.value, code2, arg2.value);

  if (warn_logical_op)
    warn_logical_operator (input_location, code, TREE_TYPE (result.value),
			   code1, arg1.value, code2, arg2.value);


  if (code == EQ_EXPR || code == NE_EXPR)
    {
      if ((code1 == STRING_CST && !integer_zerop (arg2.value))
	  || (code2 == STRING_CST && !integer_zerop (arg1.value)))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
    }
  else if (TREE_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified behavior");

  if (TREE_OVERFLOW_P (result.value)
      && !TREE_OVERFLOW_P (arg1.value)
      && !TREE_OVERFLOW_P (arg2.value))
    overflow_warning (location, result.value);


  if (warn_enum_compare
      && TREE_CODE_CLASS (code) == tcc_comparison
      && TREE_CODE (type1) == ENUMERAL_TYPE
      && TREE_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  return result;
}
