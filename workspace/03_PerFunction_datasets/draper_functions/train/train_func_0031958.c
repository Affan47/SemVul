network_masklen(PG_FUNCTION_ARGS)
{
	inet	   *ip = PG_GETARG_INET_P(0);

	PG_RETURN_INT32(ip_bits(ip));
}
