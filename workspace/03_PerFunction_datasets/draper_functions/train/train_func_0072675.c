gt_pch_p_12varpool_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct varpool_node * const x ATTRIBUTE_UNUSED = (struct varpool_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).alias_of), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_needed), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev_needed), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).same_comdat_group), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).ref_list.references), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).lto_file_data), cookie);
}
