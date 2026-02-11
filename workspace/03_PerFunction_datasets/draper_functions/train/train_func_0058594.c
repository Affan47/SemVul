v_callback_connect_terminate(const char *bye)
{
	void (* func_connect_terminate)(void *user_data, char *address, const char *bye);
	char address_string[32];

	printf("terminate (%s)\n", bye);
	func_connect_terminate = v_fs_get_user_func(2);
	v_n_get_address_string(v_con_get_network_address(), address_string);
#if defined(V_PRINT_RECEIVE_COMMANDS)
	printf("receive: verse_send_connect_terminate(address = %s, bye = %s); callback = %p\n", address_string, bye, func_connect_terminate);
#endif
	if(func_connect_terminate != 0)
		func_connect_terminate(v_fs_get_user_data(2), address_string, bye);
}
