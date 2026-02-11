ves_icall_System_Net_Sockets_Socket_GetSocketOption_arr_internal (SOCKET sock, gint32 level, gint32 name, MonoArray **byte_val, gint32 *error)
{
	int system_level = 0;
	int system_name = 0;
	int ret;
	guchar *buf;
	socklen_t valsize;

	*error = 0;

	ret=convert_sockopt_level_and_name((MonoSocketOptionLevel)level, (MonoSocketOptionName)name, &system_level,
					   &system_name);
	if(ret==-1) {
		*error = WSAENOPROTOOPT;
		return;
	}
	if(ret==-2)
		return;

	valsize=mono_array_length(*byte_val);
	buf=mono_array_addr(*byte_val, guchar, 0);

	MONO_PREPARE_BLOCKING;

	ret = _wapi_getsockopt (sock, system_level, system_name, buf, &valsize);

	MONO_FINISH_BLOCKING;

	if(ret==SOCKET_ERROR) {
		*error = WSAGetLastError ();
	}
}
