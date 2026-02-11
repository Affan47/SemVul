knot_dname_prefixlen(const uint8_t *name, unsigned nlabels, const uint8_t *pkt)
{
	if (name == NULL)
		return KNOT_EINVAL;


	if (nlabels == 0)
		return 1;


	name = knot_wire_seek_label(name, pkt);

	int len = 1;
	while (*name != '\0') {
		len += *name + 1;
		name = knot_wire_next_label(name, pkt);
		if (--nlabels == 0)
			break;
	}

	return len;
}
