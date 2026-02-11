open_socketpair(private_socket_default_socket_t *this, int family,
							int *skt, int *skt_natt, char *label)
{
	if (!use_family(family))
	{
		*skt = -1;
		*skt_natt = -1;
		return;
	}

	*skt = open_socket(this, family, &this->port);
	if (*skt == -1)
	{
		*skt_natt = -1;
		DBG1(DBG_NET, "could not open %s socket, %s disabled", label, label);
	}
	else
	{
		*skt_natt = open_socket(this, family, &this->natt);
		if (*skt_natt == -1)
		{
			DBG1(DBG_NET, "could not open %s NAT-T socket", label);
		}
	}
}
