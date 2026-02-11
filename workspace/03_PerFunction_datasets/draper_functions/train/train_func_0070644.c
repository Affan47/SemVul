is_overflow_infinity (const_tree val)
{
  return (needs_overflow_infinity (TREE_TYPE (val))
	  && CONSTANT_CLASS_P (val)
	  && TREE_OVERFLOW (val)
	  && (vrp_val_is_min (val) || vrp_val_is_max (val)));
}
