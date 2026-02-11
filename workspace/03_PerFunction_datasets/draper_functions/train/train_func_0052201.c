supports_overflow_infinity (const_tree type)
{
  tree min = vrp_val_min (type), max = vrp_val_max (type);
#ifdef ENABLE_CHECKING
  gcc_assert (needs_overflow_infinity (type));
#endif
  return (min != NULL_TREE
	  && CONSTANT_CLASS_P (min)
	  && max != NULL_TREE
	  && CONSTANT_CLASS_P (max));
}
