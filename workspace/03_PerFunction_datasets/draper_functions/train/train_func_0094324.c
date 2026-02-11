next_dom_son (enum cdi_direction dir, basic_block bb)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  struct et_node *next = bb->dom[dir_index]->right;

  return (basic_block) (next->father->son == next ? NULL : next->data);
}
