gt_pch_p_11eh_region_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct eh_region_d * const x ATTRIBUTE_UNUSED = (struct eh_region_d *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).outer), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).inner), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_peer), cookie);
  switch ((*x).type)
    {
    case ERT_TRY:
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_try.first_catch), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_try.last_catch), cookie);
      break;
    case ERT_ALLOWED_EXCEPTIONS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.allowed.type_list), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.allowed.label), cookie);
      break;
    case ERT_MUST_NOT_THROW:
      if ((void *)(x) == this_obj)
        op (&((*x).u.must_not_throw.failure_decl), cookie);
      break;
    default:
      break;
    }
  if ((void *)(x) == this_obj)
    op (&((*x).landing_pads), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).exc_ptr_reg), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).filter_reg), cookie);
}
