ambi_op_p (enum tree_code code)
{
  return (code == INDIRECT_REF
	  || code == ADDR_EXPR
	  || code == UNARY_PLUS_EXPR
	  || code == NEGATE_EXPR
	  || code == PREINCREMENT_EXPR
	  || code == PREDECREMENT_EXPR);
}
