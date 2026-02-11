mem_refs_may_alias_p (tree mem1, tree mem2, struct pointer_map_t **ttae_cache)
{


  double_int size1, size2;
  aff_tree off1, off2;


  if (!refs_may_alias_p (mem1, mem2))
    return false;


  if (optimize < 2)
    return true;

  get_inner_reference_aff (mem1, &off1, &size1);
  get_inner_reference_aff (mem2, &off2, &size2);
  aff_combination_expand (&off1, ttae_cache);
  aff_combination_expand (&off2, ttae_cache);
  aff_combination_scale (&off1, double_int_minus_one);
  aff_combination_add (&off2, &off1);

  if (aff_comb_cannot_overlap_p (&off2, size1, size2))
    return false;

  return true;
}
