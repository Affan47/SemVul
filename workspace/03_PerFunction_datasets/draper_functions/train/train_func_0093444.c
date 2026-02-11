find_uses_to_rename_use (basic_block bb, tree use, bitmap *use_blocks,
			 bitmap need_phis)
{
  unsigned ver;
  basic_block def_bb;
  struct loop *def_loop;

  if (TREE_CODE (use) != SSA_NAME)
    return;


  if (!is_gimple_reg (use))
    return;

  ver = SSA_NAME_VERSION (use);
  def_bb = gimple_bb (SSA_NAME_DEF_STMT (use));
  if (!def_bb)
    return;
  def_loop = def_bb->loop_father;


  if (!loop_outer (def_loop))
    return;


  if (flow_bb_inside_loop_p (def_loop, bb))
    return;

  if (!use_blocks[ver])
    use_blocks[ver] = BITMAP_ALLOC (NULL);
  bitmap_set_bit (use_blocks[ver], bb->index);

  bitmap_set_bit (need_phis, ver);
}
