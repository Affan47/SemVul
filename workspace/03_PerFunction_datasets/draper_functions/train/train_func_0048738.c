dse_step3_exit_block_scan (bb_info_t bb_info)
{


  if (stores_off_frame_dead_at_return)
    {
      unsigned int i;
      group_info_t group;

      FOR_EACH_VEC_ELT (group_info_t, rtx_group_vec, i, group)
	{
	  if (group->process_globally && group->frame_related)
	    bitmap_ior_into (bb_info->gen, group->group_kill);
	}
    }
}
