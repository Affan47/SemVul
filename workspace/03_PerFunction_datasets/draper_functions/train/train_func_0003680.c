VLM5030_setup_parameter(UINT8 param)
{

	VLM5030_parameter = param;


	if(param&2)
		interp_step = 4;
	else if(param&1)
		interp_step = 2;
	else
		interp_step = 1;


	VLM5030_frame_size = VLM5030_speed_table[(param>>3) &7];


	if(param&0x80)
		pitch_offset = -8;
	else if(param&0x40)
		pitch_offset = 8;
	else
		pitch_offset = 0;
}
