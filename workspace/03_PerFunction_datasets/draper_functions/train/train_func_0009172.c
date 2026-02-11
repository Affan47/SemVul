convert_network_to_scalar(Datum value, Oid typid)
{
	switch (typid)
	{
		case INETOID:
		case CIDROID:
			{
				inet	   *ip = DatumGetInetP(value);
				int			len;
				double		res;
				int			i;


				if (ip_family(ip) == PGSQL_AF_INET)
					len = 4;
				else
					len = 5;

				res = ip_family(ip);
				for (i = 0; i < len; i++)
				{
					res *= 256;
					res += ip_addr(ip)[i];
				}
				return res;

				break;
			}
		case MACADDROID:
			{
				macaddr    *mac = DatumGetMacaddrP(value);
				double		res;

				res = (mac->a << 16) | (mac->b << 8) | (mac->c);
				res *= 256 * 256 * 256;
				res += (mac->d << 16) | (mac->e << 8) | (mac->f);
				return res;
			}
	}


	elog(ERROR, "unsupported type: %u", typid);
	return 0;
}
