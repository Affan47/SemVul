valid_dline(struct Client *source_p, const char *dlhost)
{
	static char cidr_form_host[HOSTLEN + 1];
	int bits;

	rb_strlcpy(cidr_form_host, dlhost, sizeof(cidr_form_host));

	if(!parse_netmask(dlhost, NULL, &bits))
	{
		sendto_one_notice(source_p, ":Invalid D-Line");
		return 0;
	}

	if(IsOperAdmin(source_p))
	{
		if(bits < 8)
		{
			sendto_one_notice(source_p,
					  ":For safety, bitmasks less than 8 require db access.");
			return 0;
		}
	}
	else
	{
		if(bits < 16)
		{
			sendto_one_notice(source_p,
					  ":Dline bitmasks less than 16 are for admins only.");
			return 0;
		}
	}

	return 1;
}
