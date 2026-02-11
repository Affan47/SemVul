Mono_Posix_Syscall_setsockopt (int socket, int level, int option_name, void* option_value, gint64 option_len)
{
	mph_return_if_socklen_t_overflow (option_len);

	return setsockopt (socket, level, option_name, option_value, option_len);
}
