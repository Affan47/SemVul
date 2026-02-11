recv_and_check_password_packet(Port *port)
{
	char	   *passwd;
	int			result;

	passwd = recv_password_packet(port);

	if (passwd == NULL)
		return STATUS_EOF;

	result = md5_crypt_verify(port, port->user_name, passwd);

	pfree(passwd);

	return result;
}
