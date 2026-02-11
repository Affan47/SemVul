tcp_send(TCP_SOCKET *p_self, const char *p_buf, int len)
{
	if (p_self == NULL)
	{
		return RC_INVALID_POINTER;
	}

	if (!p_self->initialized)
	{
		return RC_TCP_OBJECT_NOT_INITIALIZED;
	}

	return ip_send(&p_self->super, p_buf, len);
}
