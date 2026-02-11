nearest_common_dominator (enum cdi_direction dir, basic_block bb1, basic_block bb2)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);

  gcc_checking_assert (dom_computed[dir_index]);

  if (!bb1)
    return bb2;
  if (!bb2)
    return bb1;

  return (basic_block) et_nca (bb1->dom[dir_index], bb2->dom[dir_index])->data;
}
