skip_space (const char *p, const char *end)
{
	for (; p < end && my_isspace (*p); p++)
		;
	return p;
}
