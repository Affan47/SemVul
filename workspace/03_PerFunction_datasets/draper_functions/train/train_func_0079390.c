check_case_value (tree value)
{
  if (value == NULL_TREE)
    return value;


  STRIP_TYPE_NOPS (value);


  if (c_dialect_cxx ())
    {
      value = decl_constant_value (value);
      STRIP_TYPE_NOPS (value);
      value = fold (value);
    }

  if (TREE_CODE (value) != INTEGER_CST
      && value != error_mark_node)
    {
      error ("case label does not reduce to an integer constant");
      value = error_mark_node;
    }
  else

    value = default_conversion (value);

  constant_expression_warning (value);

  return value;
}
