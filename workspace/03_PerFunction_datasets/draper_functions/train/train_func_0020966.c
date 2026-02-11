ClientAuthentication(Port *port)
{
	int			status = STATUS_ERROR;


	if (hba_getauthmethod(port) != STATUS_OK)
		ereport(FATAL,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("missing or erroneous pg_hba.conf file"),
				 errhint("See server log for details.")));

	switch (port->auth_method)
	{
		case uaReject:


			{
				char		hostinfo[NI_MAXHOST];

				pg_getnameinfo_all(&port->raddr.addr, port->raddr.salen,
								   hostinfo, sizeof(hostinfo),
								   NULL, 0,
								   NI_NUMERICHOST);

#ifdef USE_SSL
				ereport(FATAL,
						(errcode(ERRCODE_INVALID_AUTHORIZATION_SPECIFICATION),
						 errmsg("no pg_hba.conf entry for host \"%s\", user \"%s\", database \"%s\", %s",
							  hostinfo, port->user_name, port->database_name,
								port->ssl ? _("SSL on") : _("SSL off"))));
#else
				ereport(FATAL,
						(errcode(ERRCODE_INVALID_AUTHORIZATION_SPECIFICATION),
						 errmsg("no pg_hba.conf entry for host \"%s\", user \"%s\", database \"%s\"",
						   hostinfo, port->user_name, port->database_name)));
#endif
				break;
			}

		case uaKrb5:
			sendAuthRequest(port, AUTH_REQ_KRB5);
			status = pg_krb5_recvauth(port);
			break;

		case uaIdent:


#if !defined(HAVE_GETPEEREID) && !defined(SO_PEERCRED) && \
	(defined(HAVE_STRUCT_CMSGCRED) || defined(HAVE_STRUCT_FCRED) || \
	 (defined(HAVE_STRUCT_SOCKCRED) && defined(LOCAL_CREDS)))
			if (port->raddr.addr.ss_family == AF_UNIX)
			{
#if defined(HAVE_STRUCT_FCRED) || defined(HAVE_STRUCT_SOCKCRED)


				int			on = 1;

				if (setsockopt(port->sock, 0, LOCAL_CREDS, &on, sizeof(on)) < 0)
					ereport(FATAL,
							(errcode_for_socket_access(),
					   errmsg("could not enable credential reception: %m")));
#endif

				sendAuthRequest(port, AUTH_REQ_SCM_CREDS);
			}
#endif
			status = authident(port);
			break;

		case uaMD5:
			sendAuthRequest(port, AUTH_REQ_MD5);
			status = recv_and_check_password_packet(port);
			break;

		case uaCrypt:
			sendAuthRequest(port, AUTH_REQ_CRYPT);
			status = recv_and_check_password_packet(port);
			break;

		case uaPassword:
			sendAuthRequest(port, AUTH_REQ_PASSWORD);
			status = recv_and_check_password_packet(port);
			break;

#ifdef USE_PAM
		case uaPAM:
			status = CheckPAMAuth(port, port->user_name, "");
			break;
#endif

#ifdef USE_LDAP
		case uaLDAP:
			status = CheckLDAPAuth(port);
			break;
#endif

		case uaTrust:
			status = STATUS_OK;
			break;
	}

	if (status == STATUS_OK)
		sendAuthRequest(port, AUTH_REQ_OK);
	else
		auth_failed(port, status);
}
