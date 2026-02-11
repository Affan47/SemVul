default_conversion (tree exp)
{
  exp = decay_conversion (exp);

  if (INTEGRAL_OR_ENUMERATION_TYPE_P (TREE_TYPE (exp)))
    exp = perform_integral_promotions (exp);

  return exp;
}
