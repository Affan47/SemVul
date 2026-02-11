ipset_print_proto(char *buf, unsigned int len,
		  const struct ipset_data *data,
		  enum ipset_opt opt ASSERT_UNUSED,
		  uint8_t env UNUSED)
{
	const struct protoent *protoent;
	uint8_t proto;

	assert(buf);
	assert(len > 0);
	assert(data);
	assert(opt == IPSET_OPT_PROTO);

	proto = *(const uint8_t *) ipset_data_get(data, IPSET_OPT_PROTO);
	assert(proto);

	protoent = getprotobynumber(proto);
	if (protoent)
		return snprintf(buf, len, "%s", protoent->p_name);


	return snprintf(buf, len, "%u", proto);
}
