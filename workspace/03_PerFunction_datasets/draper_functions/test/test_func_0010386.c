authident(hbaPort *port)
{
	char		ident_user[IDENT_USERNAME_MAX + 1];

	if (get_role_line(port->user_name) == NULL)
		return STATUS_ERROR;

	switch (port->raddr.addr.ss_family)
	{
		case AF_INET:
#ifdef	HAVE_IPV6
		case AF_INET6:
#endif
			if (!ident_inet(port->raddr, port->laddr, ident_user))
				return STATUS_ERROR;
			break;

#ifdef HAVE_UNIX_SOCKETS
		case AF_UNIX:
			if (!ident_unix(port->sock, ident_user))
				return STATUS_ERROR;
			break;
#endif

		default:
			return STATUS_ERROR;
	}

	ereport(DEBUG2,
			(errmsg("Ident protocol identifies remote user as \"%s\"",
					ident_user)));

	if (check_ident_usermap(port->auth_arg, port->user_name, ident_user))
		return STATUS_OK;
	else
		return STATUS_ERROR;
}
