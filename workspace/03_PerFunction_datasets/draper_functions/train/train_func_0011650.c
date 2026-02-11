BIO_get_port(const char *str, unsigned short *port_ptr)
	{
	int i;
	struct servent *s;

	if (str == NULL)
		{
		BIOerr(BIO_F_BIO_GET_PORT,BIO_R_NO_PORT_DEFINED);
		return(0);
		}
	i=atoi(str);
	if (i != 0)
		*port_ptr=(unsigned short)i;
	else
		{
		CRYPTO_w_lock(CRYPTO_LOCK_GETSERVBYNAME);


#ifndef CONST_STRICT
		s=getservbyname((char *)str,"tcp");
#else
		s=getservbyname(str,"tcp");
#endif
		if(s != NULL)
			*port_ptr=ntohs((unsigned short)s->s_port);
		CRYPTO_w_unlock(CRYPTO_LOCK_GETSERVBYNAME);
		if(s == NULL)
			{
			if (strcmp(str,"http") == 0)
				*port_ptr=80;
			else if (strcmp(str,"telnet") == 0)
				*port_ptr=23;
			else if (strcmp(str,"socks") == 0)
				*port_ptr=1080;
			else if (strcmp(str,"https") == 0)
				*port_ptr=443;
			else if (strcmp(str,"ssl") == 0)
				*port_ptr=443;
			else if (strcmp(str,"ftp") == 0)
				*port_ptr=21;
			else if (strcmp(str,"gopher") == 0)
				*port_ptr=70;
#if 0
			else if (strcmp(str,"wais") == 0)
				*port_ptr=21;
#endif
			else
				{
				SYSerr(SYS_F_GETSERVBYNAME,get_last_socket_error());
				ERR_add_error_data(3,"service='",str,"'");
				return(0);
				}
			}
		}
	return(1);
	}
