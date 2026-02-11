special_function_p (const_tree decl)
{


  if (DECL_COPY_CONSTRUCTOR_P (decl))
    return sfk_copy_constructor;
  if (DECL_MOVE_CONSTRUCTOR_P (decl))
    return sfk_move_constructor;
  if (DECL_CONSTRUCTOR_P (decl))
    return sfk_constructor;
  if (DECL_OVERLOADED_OPERATOR_P (decl) == NOP_EXPR)
    {
      if (copy_fn_p (decl))
	return sfk_copy_assignment;
      if (move_fn_p (decl))
	return sfk_move_assignment;
    }
  if (DECL_MAYBE_IN_CHARGE_DESTRUCTOR_P (decl))
    return sfk_destructor;
  if (DECL_COMPLETE_DESTRUCTOR_P (decl))
    return sfk_complete_destructor;
  if (DECL_BASE_DESTRUCTOR_P (decl))
    return sfk_base_destructor;
  if (DECL_DELETING_DESTRUCTOR_P (decl))
    return sfk_deleting_destructor;
  if (DECL_CONV_FN_P (decl))
    return sfk_conversion;

  return sfk_none;
}
