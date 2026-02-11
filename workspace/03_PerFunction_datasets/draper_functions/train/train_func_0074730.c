network_broadcast(PG_FUNCTION_ARGS)
{
	inet	   *ip = PG_GETARG_INET_P(0);
	inet	   *dst;
	int			byte;
	int			bits;
	int			maxbytes;
	unsigned char mask;
	unsigned char *a,
			   *b;


	dst = (inet *) palloc0(VARHDRSZ + sizeof(inet_struct));

	if (ip_family(ip) == PGSQL_AF_INET)
		maxbytes = 4;
	else
		maxbytes = 16;

	bits = ip_bits(ip);
	a = ip_addr(ip);
	b = ip_addr(dst);

	for (byte = 0; byte < maxbytes; byte++)
	{
		if (bits >= 8)
		{
			mask = 0x00;
			bits -= 8;
		}
		else if (bits == 0)
			mask = 0xff;
		else
		{
			mask = 0xff >> bits;
			bits = 0;
		}

		b[byte] = a[byte] | mask;
	}

	ip_family(dst) = ip_family(ip);
	ip_bits(dst) = ip_bits(ip);
	VARATT_SIZEP(dst) = VARHDRSZ +
		((char *) ip_addr(dst) - (char *) VARDATA(dst)) +
		ip_addrsize(dst);

	PG_RETURN_INET_P(dst);
}
