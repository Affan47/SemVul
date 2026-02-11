can_construe_as_integer(const char *text)
{

	if (*text == '\0')
		return true;


	if ((*text != '+') && (*text != '-') && !isdigit(*text))
		return false;


	for (const char *p = text + 1; *p != '\0'; p++)
	{
		if (!isdigit(*p))
			return false;
	}

	return true;
}
