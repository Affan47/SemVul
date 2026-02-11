is_and_or_or (enum tree_code tc, tree typ)
{
  return (tc == TRUTH_AND_EXPR
          || tc == TRUTH_OR_EXPR
          || tc == BIT_IOR_EXPR
          || (tc == BIT_AND_EXPR
              && (typ == 0 || TREE_CODE (typ) == BOOLEAN_TYPE)));
}
