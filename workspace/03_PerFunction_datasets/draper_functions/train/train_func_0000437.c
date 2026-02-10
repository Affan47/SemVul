parse_message_line(char *line)
{
	char *rest;

	switch(GetTokenIndex(line, message_options, -1, &rest))
	{
	case 0:
		parse_colorset(rest);
		break;
	}
}
