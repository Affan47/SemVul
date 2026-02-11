v_send_hidden_connect_accept(void)
{
	uint8 buf[1500], *client_key, encrypted[V_ENCRYPTION_DATA_KEY_SIZE];
	unsigned int i, buffer_pos = 0;

	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], 1);
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 1);
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], verse_session_get_avatar());
	client_key = v_con_get_other_key();
	v_e_connect_encrypt(encrypted, v_con_get_data_key(), &client_key[V_ENCRYPTION_LOGIN_PUBLIC_START], &client_key[V_ENCRYPTION_LOGIN_N_START]);
	for(i = 0; i < V_ENCRYPTION_DATA_KEY_SIZE; i++)
		buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], encrypted[i]);
	v_n_send_data(v_con_get_network_address(), buf, buffer_pos);
}
