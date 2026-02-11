cidr_set_masklen(PG_FUNCTION_ARGS)
{
	inet	   *src = PG_GETARG_INET_P(0);
	int			bits = PG_GETARG_INT32(1);
	inet	   *dst;
	int byte;
	int			nbits;
	int			maxbytes;

	if (bits == -1)
		bits = ip_maxbits(src);

	if ((bits < 0) || (bits > ip_maxbits(src)))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid mask length: %d", bits)));


	dst = (inet *) palloc(VARSIZE_ANY(src));
	memcpy(dst, src, VARSIZE_ANY(src));

	ip_bits(dst) = bits;


	byte = bits / 8;

	nbits = bits % 8;

	if (nbits != 0)
	{
		ip_addr(dst)[byte] &=~(0xFF >> nbits);
		byte	  ++;
	}

	maxbytes = ip_addrsize(dst);
	while (byte <maxbytes)
	{
		ip_addr(dst)[byte] = 0;
		byte	  ++;
	}

	PG_RETURN_INET_P(dst);
}
