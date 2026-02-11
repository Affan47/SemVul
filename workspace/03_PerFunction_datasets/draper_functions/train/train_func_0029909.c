init_r_info(void)
{
	int i;
	errr err;


	init_header(&r_head, z_info->r_max, sizeof(monster_race));


	r_head.parse_info_txt = parse_r_info;


	r_head.eval_info_post = eval_r_power;


	if (arg_rebalance) r_head.emit_info_txt_index = emit_r_info_index;

	err = init_info("monster", &r_head);


	r_info = r_head.info_ptr;
	r_name = r_head.name_ptr;
	r_text = r_head.text_ptr;
	tot_mon_power = 0;
	for (i = 0; i < z_info->r_max; i++)
	{
		tot_mon_power += r_info[i].power;
	}

	return (err);
}
