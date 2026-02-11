free_dominance_info (info)
     dominance_info info;
{
  basic_block bb;


  FOR_EACH_BB (bb)
    if (bb->index < (int)(info->varray->num_elements - 2)
	&& BB_NODE (info, bb))
      delete_from_dominance_info (info, bb);
  delete_from_dominance_info (info, ENTRY_BLOCK_PTR);
  delete_from_dominance_info (info, EXIT_BLOCK_PTR);
  et_forest_delete (info->forest);
  VARRAY_GROW (info->varray, 0);
  free (info);
}
