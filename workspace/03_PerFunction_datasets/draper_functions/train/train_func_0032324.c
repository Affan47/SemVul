value_dependent_init_p (tree init)
{
  if (TREE_CODE (init) == TREE_LIST)

    return any_value_dependent_elements_p (init);
  else if (TREE_CODE (init) == CONSTRUCTOR)

    {
      VEC(constructor_elt, gc) *elts;
      size_t nelts;
      size_t i;

      elts = CONSTRUCTOR_ELTS (init);
      nelts = VEC_length (constructor_elt, elts);
      for (i = 0; i < nelts; ++i)
	if (value_dependent_init_p (VEC_index (constructor_elt,
					       elts, i)->value))
	  return true;
    }
  else

    return value_dependent_expression_p (init);

  return false;
}
