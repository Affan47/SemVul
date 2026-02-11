verse_send_node_destroy(VNodeID node_id)
{
	uint8 *buf;
	unsigned int buffer_pos = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_10);
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 10);
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_node_destroy(node_id = %u );\n", node_id);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], (uint8)-1);
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], (uint8)-1);
	if(node_id == (uint32) ~0u)
		v_cmd_buf_set_unique_address_size(head, 5);
	else
		v_cmd_buf_set_address_size(head, 5);
	v_cmd_buf_set_size(head, buffer_pos);
	v_noq_send_buf(v_con_get_network_queue(), head);
}
