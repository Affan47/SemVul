v_unpack_g_crease_set_vertex(const char *buf, size_t buffer_length)
{
	unsigned int buffer_pos = 0;
	void (* func_g_crease_set_vertex)(void *user_data, VNodeID node_id, const char *layer, uint32 def_crease);
	VNodeID node_id;
	char layer[16];
	uint32 def_crease;

	func_g_crease_set_vertex = v_fs_get_user_func(62);
	if(buffer_length < 4)
		return -1;
	buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &node_id);
	buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], layer, 16, buffer_length - buffer_pos);
	if(buffer_length < 4 + buffer_pos)
		return -1;
	buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &def_crease);
#if defined V_PRINT_RECEIVE_COMMANDS
	printf("receive: verse_send_g_crease_set_vertex(node_id = %u layer = %s def_crease = %u ); callback = %p\n", node_id, layer, def_crease, v_fs_get_user_func(62));
#endif
	if(func_g_crease_set_vertex != NULL)
		func_g_crease_set_vertex(v_fs_get_user_data(62), node_id, layer, def_crease);

	return buffer_pos;
}
