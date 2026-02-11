deinit()
{
	if(init_flag)
	{
		mem_del(rock_info_array);
		mem_del(rock_block_array);
		mem_del(rock_bitmap_array);
		mem_del(rock_anim_array);
		rock_info_count = 0;
		rock_block_count = 0;
		rock_bitmap_count = 0;
		rock_anim_count = 0;

		res_bitmap.deinit();

		init_flag = 0;
	}
}
