lambda_capture_field_type (tree expr)
{
  tree type;
  if (type_dependent_expression_p (expr)
      && !(TREE_TYPE (expr) && TREE_CODE (TREE_TYPE (expr)) == POINTER_TYPE))
    {
      type = cxx_make_type (DECLTYPE_TYPE);
      DECLTYPE_TYPE_EXPR (type) = expr;
      DECLTYPE_FOR_LAMBDA_CAPTURE (type) = true;
      SET_TYPE_STRUCTURAL_EQUALITY (type);
    }
  else
    type = non_reference (unlowered_expr_type (expr));
  return type;
}
