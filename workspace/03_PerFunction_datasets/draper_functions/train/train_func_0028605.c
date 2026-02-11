syslog_decode(char *name, CODE *codetab)
{
	CODE *c;

	if (isdigit((unsigned char)*name))
		return atoi(name);

	for (c = codetab; c->c_name; c++)
		if (! strcasecmp(name, c->c_name))
			return c->c_val;

	return -1;
}
