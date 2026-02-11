isns_policy_object_type_print(const isns_value_t *vp, char *buf, size_t size)
{
	unsigned int	i, pos = 0;
	uint32_t	mask;
	const char	*sepa = "";

	mask = vp->iv_uint32;
	if (mask == 0) {
		snprintf(buf, size, "<empty>");
		return;
	}

	for (i = 0; i < 32; ++i, mask >>= 2) {
		const char	*name;

		if (!(mask & 3))
			continue;

		name = policy_object_type_bit_names[i];
		if (name)
			snprintf(buf + pos, size - pos, "%s%s:%s%s", sepa, name,
				(mask & ISNS_PERMISSION_READ)? "r" : "",
				(mask & ISNS_PERMISSION_WRITE)? "w" : "");
		else
			snprintf(buf + pos, size - pos, "%sbit%u:%s%s",sepa,  i,
				(mask & ISNS_PERMISSION_READ)? "r" : "",
				(mask & ISNS_PERMISSION_WRITE)? "w" : "");
		sepa = ", ";
		pos = strlen(buf);
	}
}
