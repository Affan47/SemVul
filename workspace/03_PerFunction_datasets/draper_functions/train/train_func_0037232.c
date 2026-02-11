gt_pch_p_12ptr_info_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct ptr_info_def * x ATTRIBUTE_UNUSED = (struct ptr_info_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).pt.vars), cookie);
}
