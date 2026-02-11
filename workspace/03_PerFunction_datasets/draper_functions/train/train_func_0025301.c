cmd_istr(str)
	char *str;
{
	char *s;
	int action;
	char *endline = str + strlen(str);

	for (s = str;  *s != '\0';  )
	{
		char *os = s;
		step_char(&s, +1, endline);
		action = cmd_ichar(os, s - os);
		if (action != CC_OK)
		{
			bell();
			return (action);
		}
	}
	return (CC_OK);
}
