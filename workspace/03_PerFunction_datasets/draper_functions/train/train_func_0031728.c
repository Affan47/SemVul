v_unpack_o_anim_run(const char *buf, size_t buffer_length)
{
	unsigned int buffer_pos = 0;
	void (* func_o_anim_run)(void *user_data, VNodeID node_id, uint16 link_id, uint32 time_s, uint32 time_f, uint8 dimensions, const real64 *pos, const real64 *speed, const real64 *accel, const real64 *scale, const real64 *scale_speed);
	VNodeID node_id;
	uint16 link_id;
	uint32 time_s;
	uint32 time_f;
	uint8 dimensions;
	const real64 *pos;
	const real64 *speed;
	const real64 *accel;
	const real64 *scale;
	const real64 *scale_speed;

	func_o_anim_run = v_fs_get_user_func(45);
	if(buffer_length < 6)
		return -1;
	buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &node_id);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &link_id);
	buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &time_s);
	buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &time_f);
	buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &dimensions);
#if defined V_PRINT_RECEIVE_COMMANDS
	printf("receive: verse_send_o_anim_run(node_id = %u link_id = %u time_s = %u time_f = %u dimensions = %u ); callback = %p\n", node_id, link_id, time_s, time_f, dimensions, v_fs_get_user_func(45));
#endif
	{
		double output[5][4];
		unsigned int i, j;
		char mask, pow = 1;
		buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &mask);
		if(dimensions > 4)
			dimensions = 4;
		for(j = 0; j < dimensions; j++)
			buffer_pos += vnp_raw_unpack_real64(&buf[buffer_pos], &output[0][j]);
		for(i = 1; i < 5; i++)
		{
			if((mask & pow) != 0)
				for(j = 0; j < dimensions; j++)
					buffer_pos += vnp_raw_unpack_real64(&buf[buffer_pos], &output[i][j]);
			else
				for(j = 0; j < dimensions; j++)
					output[i][j] = 0;
			pow *= 2;
		}
		if(func_o_anim_run != NULL)
			func_o_anim_run(v_fs_get_user_data(45), node_id, link_id, time_s, time_f, dimensions, &output[0][0], &output[1][0], &output[2][0], &output[3][0], &output[4][0]);
		return buffer_pos;
	}

	if(func_o_anim_run != NULL)
		func_o_anim_run(v_fs_get_user_data(45), node_id, link_id, time_s, time_f, dimensions, pos, speed, accel, scale, scale_speed);

	return buffer_pos;
}
