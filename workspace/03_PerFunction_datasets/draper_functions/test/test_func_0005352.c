verse_send_o_method_create(VNodeID node_id, uint16 group_id, uint16 method_id, const char *name, uint8 param_count, const VNOParamType *param_types, const char * *param_names)
{
	uint8 *buf;
	unsigned int buffer_pos = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_1500);
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 43);
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_o_method_create(node_id = %u group_id = %u method_id = %u name = %s param_count = %u param_types = %p param_names = %p );\n", node_id, group_id, method_id, name, param_count, param_types, param_names);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], group_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], method_id);
	buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], name, 512);
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], param_count);
	{
		unsigned int i, j, sum = 1;
		for(i = 0; i < param_count; i++)
		{
			sum += 3;
			for(j = 0; param_names[i][j] != 0; j++);
		}
		if(sum + buffer_pos > 1500)
			return;
		for(i = 0; i < param_count; i++)
		{
			buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], param_types[i]);
			buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], param_names[i], 1500 - buffer_pos);
		}
	}
	if(node_id == (uint32) ~0u || group_id == (uint16) ~0u || method_id == (uint16) ~0u)
		v_cmd_buf_set_unique_address_size(head, 9);
	else
		v_cmd_buf_set_address_size(head, 9);
	v_cmd_buf_set_size(head, buffer_pos);
	v_noq_send_buf(v_con_get_network_queue(), head);
}
