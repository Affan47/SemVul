isupport_extban(const void *ptr)
{
	const char *p;
	static char result[200];

	p = get_extban_string();
	if (EmptyString(p))
		return NULL;
	rb_snprintf(result, sizeof result, "$,%s", p);
	return result;
}
