mangle_wildcard_to_cidr(const char *text)
{
	static char buf[20];
	static const char *splat = "*", *dot = ".";
	char *p, *q, *n1, *n2, *n3, *n4;

	q = LOCAL_COPY(text);

	n1 = rb_strtok_r(q, dot, &p);
	n2 = rb_strtok_r(NULL, dot, &p);
	n3 = rb_strtok_r(NULL, dot, &p);
	n4 = rb_strtok_r(NULL, dot, &p);

	if(n1 == NULL)
		return NULL;


	if(!strcmp(n1, splat) || !is_ip_number(n1))
		return NULL;

	if(n2 == NULL || !strcmp(n2, splat))
	{
		if(n3 == NULL || (!strcmp(n3, splat) && (n4 == NULL || !strcmp(n4, splat))))
		{
			rb_snprintf(buf, sizeof(buf), "%s.0.0.0/8", n1);
			return buf;
		}
	}

	if(!is_ip_number(n2))
		return NULL;

	if(n3 == NULL || !strcmp(n3, splat))
	{
		if(n4 == NULL || !strcmp(n4, splat))
		{
			rb_snprintf(buf, sizeof(buf), "%s.%s.0.0/16", n1, n2);
			return buf;
		}
	}

	if(!is_ip_number(n3))
		return NULL;

	if(n4 == NULL || !strcmp(n4, splat))
	{
		rb_snprintf(buf, sizeof(buf), "%s.%s.%s.0/24", n1, n2, n3);
		return buf;
	}

	return NULL;
}
