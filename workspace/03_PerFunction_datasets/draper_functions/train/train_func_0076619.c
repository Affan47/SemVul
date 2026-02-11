of_device_get_modalias(struct device *dev, char *str, ssize_t len)
{
	const char *compat;
	int cplen, i;
	ssize_t tsize, csize, repend;

	if ((!dev) || (!dev->of_node))
		return -ENODEV;


	csize = snprintf(str, len, "of:N%sT%s", dev->of_node->name,
			 dev->of_node->type);


	compat = of_get_property(dev->of_node, "compatible", &cplen);
	if (!compat)
		return csize;


	for (i = (cplen - 1); i >= 0 && !compat[i]; i--)
		cplen--;
	if (!cplen)
		return csize;
	cplen++;


	tsize = csize + cplen;
	repend = tsize;

	if (csize >= len)
		return tsize;

	if (tsize >= len) {
		cplen = len - csize - 1;
		repend = len;
	}


	memcpy(&str[csize + 1], compat, cplen);
	for (i = csize; i < repend; i++) {
		char c = str[i];
		if (c == '\0')
			str[i] = 'C';
		else if (c == ' ')
			str[i] = '_';
	}

	return tsize;
}
