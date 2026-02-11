gt_pch_p_12object_block (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct object_block * x ATTRIBUTE_UNUSED = (struct object_block *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).sect), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).objects), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).anchors), cookie);
}
