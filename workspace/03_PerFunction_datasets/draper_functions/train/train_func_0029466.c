verse_send_g_layer_destroy(VNodeID node_id, VLayerID layer_id)
{
	uint8 *buf;
	unsigned int buffer_pos = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_80);
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 48);
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_g_layer_destroy(node_id = %u layer_id = %u );\n", node_id, layer_id);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], layer_id);
	buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], NULL, 16);
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], (uint8)-1);
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], -1);
	buffer_pos += vnp_raw_pack_real64(&buf[buffer_pos], V_REAL64_MAX);
	if(node_id == (uint32) ~0u || layer_id == (uint16) ~0u)
		v_cmd_buf_set_unique_address_size(head, 7);
	else
		v_cmd_buf_set_address_size(head, 7);
	v_cmd_buf_set_size(head, buffer_pos);
	v_noq_send_buf(v_con_get_network_queue(), head);
}
