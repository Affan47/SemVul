ipset_print_number(char *buf, unsigned int len,
		   const struct ipset_data *data, enum ipset_opt opt,
		   uint8_t env UNUSED)
{
	size_t maxsize;
	const void *number;

	assert(buf);
	assert(len > 0);
	assert(data);

	number = ipset_data_get(data, opt);
	maxsize = ipset_data_sizeof(opt, AF_INET);
	D("opt: %u, maxsize %zu", opt, maxsize);
	if (maxsize == sizeof(uint8_t))
		return snprintf(buf, len, "%u", *(const uint8_t *) number);
	else if (maxsize == sizeof(uint16_t))
		return snprintf(buf, len, "%u", *(const uint16_t *) number);
	else if (maxsize == sizeof(uint32_t))
		return snprintf(buf, len, "%lu",
				(long unsigned) *(const uint32_t *) number);
	else if (maxsize == sizeof(uint64_t))
		return snprintf(buf, len, "%llu",
				(long long unsigned) *(const uint64_t *) number);
	else
		assert(0);
	return 0;
}
