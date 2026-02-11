dse_step2_nospill (void)
{
  unsigned int i;
  group_info_t group;


  current_position = 1;

  FOR_EACH_VEC_ELT (group_info_t, rtx_group_vec, i, group)
    {
      bitmap_iterator bi;
      unsigned int j;

      if (group == clear_alias_group)
	continue;

      memset (group->offset_map_n, 0, sizeof(int) * group->offset_map_size_n);
      memset (group->offset_map_p, 0, sizeof(int) * group->offset_map_size_p);
      bitmap_clear (group->group_kill);

      EXECUTE_IF_SET_IN_BITMAP (group->store2_n, 0, j, bi)
	{
	  bitmap_set_bit (group->group_kill, current_position);
	  group->offset_map_n[j] = current_position++;
	  group->process_globally = true;
	}
      EXECUTE_IF_SET_IN_BITMAP (group->store2_p, 0, j, bi)
	{
	  bitmap_set_bit (group->group_kill, current_position);
	  group->offset_map_p[j] = current_position++;
	  group->process_globally = true;
	}
    }
  return current_position != 1;
}
